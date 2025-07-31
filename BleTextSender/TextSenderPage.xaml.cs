using BleTextSender.Helpers;
using BleTextSender.Services;

namespace BleTextSender;

public partial class TextSenderPage : ContentPage
{
    public TextSenderPage()
    {
        InitializeComponent();
        _bleService = ServiceHelper.GetService<IBleService>();
    }

    protected override async void OnAppearing()
    {
        base.OnAppearing();
        DeviceLabel.Text = _bleService.ConnectedDeviceName ?? "(Kein Gerät)";
        await Notifier.ShowToastAsync("Peeker: Textmodus aktiviert");
    }

    private readonly IBleService _bleService;

    private async void OnClearClicked(object sender, EventArgs e)
    {
        try
        {
            var ble = ServiceHelper.GetService<IBleService>();
            var sendTask = ble.SendTextAsync(" ");
            var ToastTask = Notifier.ShowToastAsync("Zahl gelöscht");
            await Task.WhenAll(sendTask, ToastTask);
            TextEntry.Text = string.Empty;
        }
        catch (Exception ex)
        {
            await Notifier.ShowErrorAsync("Fehler beim Löschen: " + ex.Message);
        }
    }

    private async void OnSendClicked(object sender, EventArgs e)
    {
        var text = TextEntry.Text?.Trim();
        if (string.IsNullOrEmpty(text))
        {
            StatusLabel.Text = "Bitte gib einen Text ein.";
            return;
        }

        var success = await _bleService.SendTextAsync(text);
        StatusLabel.Text = success ? "Gesendet." : "Senden fehlgeschlagen.";
    }
}