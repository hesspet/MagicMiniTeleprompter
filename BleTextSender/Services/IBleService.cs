namespace BleTextSender.Services;

/// <summary>
/// Simple service to seperate BLE logic from the UI.
/// </summary>
public interface IBleService
{
    string? ConnectedDeviceName { get; }

    Task<bool> ConnectToDeviceAsync(string deviceId);

    Task DisconnectAsync();

    Task<bool> SendTextAsync(string message);

    /// <summary>
    /// Search for BLE devices and invoke the callback for each found device.
    /// </summary>
    /// <param name="onDeviceFound"></param>
    /// <returns></returns>
    Task StartScanningAsync(Action<string, string> onDeviceFound);

    Task StopScanningAsync();
}