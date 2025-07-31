using Microsoft.Maui.Controls;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Linq;
using BleTextSender.Helpers;
using BleTextSender.Services;
using System;

namespace BleTextSender
{
    public partial class CardsPage : ContentPage
    {
        public CardsPage()
        {
            InitializeComponent();
            BindingContext = new CardsViewModel();
        }

        private static string GetCardAbbreviationFromPath(string path)
        {
            var filename = Path.GetFileNameWithoutExtension(path); // z. B. "card_queen_of_spadestwo"
            if (filename.StartsWith("card_"))
                filename = filename.Substring(5);

            if (filename.EndsWith("two"))
                filename = filename.Substring(0, filename.Length - 3); // Bildkarten-Endung entfernen

            var parts = filename.Split('_'); // z. B. ["queen", "of", "spades"]
            if (parts.Length < 3)
                return "???";

            var value = parts[0].ToLower();
            var suit = parts[2].ToLower();

            var valueMap = new Dictionary<string, string>(StringComparer.OrdinalIgnoreCase)
            {
                ["ace"] = "A",
                ["two"] = "2",
                ["three"] = "3",
                ["four"] = "4",
                ["five"] = "5",
                ["six"] = "6",
                ["seven"] = "7",
                ["eight"] = "8",
                ["nine"] = "9",
                ["ten"] = "10",
                ["jack"] = "J",
                ["queen"] = "Q",
                ["king"] = "K"
            };

            var suitMap = new Dictionary<string, string>(StringComparer.OrdinalIgnoreCase)
            {
                ["clubs"] = "C",
                ["diamonds"] = "D",
                ["hearts"] = "H",
                ["spades"] = "S"
            };

            return (valueMap.TryGetValue(value, out var shortValue) &&
                    suitMap.TryGetValue(suit, out var shortSuit))
                ? $"{shortValue}{shortSuit}"
                : "???";
        }

        private async void OnCardSelected(object sender, SelectionChangedEventArgs e)
        {
            if (e.CurrentSelection.FirstOrDefault() is string selectedPath)
            {
                var abbr = GetCardAbbreviationFromPath(selectedPath);
                await Notifier.ShowToastAsync($"Karte: {abbr}");

                // 2. BLE senden
                try
                {
                    var toastTask = Notifier.ShowToastAsync($"Karte: {abbr}");
                    var sendTask = ServiceHelper.GetService<IBleService>().SendTextAsync(abbr);

                    await Task.WhenAll(toastTask, sendTask);
                }
                catch (Exception ex)
                {
                    await Notifier.ShowErrorAsync("Senden fehlgeschlagen: " + ex.Message);
                }
            }
        }

        private async void OnClearClicked(object sender, EventArgs e)
        {
            try
            {
                // Auswahl aufheben
                CardGrid.SelectedItem = null;

                var ble = ServiceHelper.GetService<IBleService>();
                var sendTask = ble.SendTextAsync(" ");

                var ToastTask = Notifier.ShowToastAsync("Auswahl gelöscht");
                await Task.WhenAll(sendTask, ToastTask);
            }
            catch (Exception ex)
            {
                await Notifier.ShowErrorAsync("Fehler beim Löschen: " + ex.Message);
            }
        }
    }

    public class CardsViewModel : INotifyPropertyChanged
    {
        public CardsViewModel()
        {
            foreach (var suit in Suits)
            {
                AceCards.Add($"{CardPath}card_ace_of_{suit}.svg");
            }

            SelectedSuitImage = "clubs"; // Default
        }

        public event PropertyChangedEventHandler PropertyChanged;

        public ObservableCollection<string> AceCards { get; } = new();
        public ObservableCollection<string> FilteredCards { get; } = new();

        public string SelectedSuitImage
        {
            get => selectedSuit;
            set
            {
                if (selectedSuit != value)
                {
                    selectedSuit = value;
                    OnPropertyChanged();
                    ExtractSuitFromImage();
                    UpdateFilteredCards();
                }
            }
        }

        private const string CardPath = "Resources/Images/poker52/";
        private readonly string[] Suits = { "clubs", "spades", "hearts", "diamonds" };

        private readonly string[] Values = {
            "ace", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
            "jack", "queen", "king"
        };

        private string selectedSuit;

        private void ExtractSuitFromImage()
        {
            if (string.IsNullOrWhiteSpace(SelectedSuitImage))
                return;

            var filename = System.IO.Path.GetFileNameWithoutExtension(SelectedSuitImage);

            if (filename.Contains("of_"))
            {
                var parts = filename.Split(new[] { "of_" }, System.StringSplitOptions.None);
                if (parts.Length == 2)
                {
                    var suffix = parts[1]; // z.B. "hearts", "spadestwo"
                    if (suffix.EndsWith("two") && (suffix.Contains("spades") || suffix.Contains("clubs") || suffix.Contains("hearts") || suffix.Contains("diamonds")))
                        selectedSuit = suffix.Replace("two", ""); // bei Bildkarten
                    else
                        selectedSuit = suffix;
                }
            }
        }

        private void OnPropertyChanged([CallerMemberName] string name = "") =>
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));

        private void UpdateFilteredCards()
        {
            FilteredCards.Clear();

            foreach (var value in Values)
            {
                string filename = value switch
                {
                    "jack" or "queen" or "king" =>
                        $"{CardPath}card_{value}_of_{selectedSuit}two.svg", // Bildkarten: ...two.svg
                    _ =>
                        $"{CardPath}card_{value}_of_{selectedSuit}.svg"
                };

                FilteredCards.Add(filename);
            }
        }
    }
}