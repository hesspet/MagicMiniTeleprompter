using BleTextSender.Helpers;
using BleTextSender.Services;

namespace BleTextSender;

public partial class DialPadPage : ContentPage
{
    public DialPadPage()
    {
        InitializeComponent();

        try
        {
            _bleService = ServiceHelper.GetService<IBleService>();
        }
        catch (Exception ex)
        {
            Console.WriteLine("BLE Service nicht verfügbar: " + ex.Message);
        }
    }

    protected override async void OnAppearing()
    {
        base.OnAppearing();

        await Notifier.ShowToastAsync("Peeker: Pad Modus aktiviert");
    }

    private readonly IBleService _bleService;
    private Button? _lastPressedButton;
    private Color? _lastPressedOriginalColor;

    private async void OnButtonClicked(object sender, EventArgs e)
    {
        if (sender is Button button && !string.IsNullOrWhiteSpace(button.Text))
        {
            // Vorherigen Button zurücksetzen
            if (_lastPressedButton != null && _lastPressedOriginalColor != null)
            {
                _lastPressedButton.BackgroundColor = _lastPressedOriginalColor;
            }

            // Farbe merken (nur einmal – für den ersten Klick)
            _lastPressedOriginalColor = button.BackgroundColor;

            // Aktuellen Button markieren
            button.BackgroundColor = Colors.LightBlue;
            _lastPressedButton = button;

            SelectedNumberLabel.Text = button.Text;
            await _bleService.SendTextAsync(button.Text);
        }
    }

    private async void OnClearClicked(object sender, EventArgs e)
    {
        try
        {
            // Farbmarkierung zurücksetzen
            if (_lastPressedButton != null && _lastPressedOriginalColor != null)
            {
                _lastPressedButton.BackgroundColor = _lastPressedOriginalColor;
                _lastPressedButton = null;
            }

            SelectedNumberLabel.Text = string.Empty;

            var ble = ServiceHelper.GetService<IBleService>();
            var sendTask = ble.SendTextAsync(" ");
            var toastTask = Notifier.ShowToastAsync("Zahl gelöscht");
            await Task.WhenAll(sendTask, toastTask);
        }
        catch (Exception ex)
        {
            await Notifier.ShowErrorAsync("Fehler beim Löschen: " + ex.Message);
        }
    }
}