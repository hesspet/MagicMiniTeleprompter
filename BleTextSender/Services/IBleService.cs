namespace BleTextSender.Services;

public interface IBleService
{
    string? ConnectedDeviceName { get; }

    Task<bool> ConnectToDeviceAsync(string deviceId);

    Task DisconnectAsync();

    Task<bool> SendTextAsync(string message);

    Task StartScanningAsync(Action<string, string> onDeviceFound);

    Task StopScanningAsync();
}