using BleTextSender.Helpers;
using BleTextSender.Services;
using System.Collections.ObjectModel;

namespace BleTextSender;

public partial class ScanPage : ContentPage
{
    public ScanPage()
    {
        InitializeComponent();
        _bleService = ServiceHelper.GetService<IBleService>();
        DeviceListView.ItemsSource = _devices;
    }

    protected override async void OnAppearing()
    {
        base.OnAppearing();
        await Notifier.ShowToastAsync("Suche Peeker");
        _devices.Clear();

        await _bleService.StartScanningAsync((name, id) =>
        {
            MainThread.BeginInvokeOnMainThread(() =>
            {
                if (_devices.All(d => d.Id != id))
                    _devices.Add(new DeviceViewModel { Name = name ?? "(Unbenannt)", Id = id });
            });
        });
    }

    protected override async void OnDisappearing()
    {
        base.OnDisappearing();
        await _bleService.StopScanningAsync();
    }

    private readonly IBleService _bleService;
    private readonly ObservableCollection<DeviceViewModel> _devices = new();

    private async void DeviceListView_SelectionChanged(object sender, SelectionChangedEventArgs e)
    {
        if (e.CurrentSelection.FirstOrDefault() is DeviceViewModel selected)
        {
            await _bleService.StopScanningAsync();

            var success = await _bleService.ConnectToDeviceAsync(selected.Id);
            if (success)
            {
                await Notifier.ShowToastAsync("Peeker ausgewählt und steht bereit");
                await Shell.Current.GoToAsync("//TextSenderPage");
            }
            else
            {
                await Notifier.ShowErrorAsync("Peeker Verbindg fehlgeschlagen");
                await DisplayAlert("Fehler", "Verbindung fehlgeschlagen", "OK");
            }
        }
    }

    private class DeviceViewModel
    {
        public string Id { get; set; } = string.Empty;
        public string Name { get; set; } = string.Empty;
    }
}