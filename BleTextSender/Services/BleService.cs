using Microsoft.Extensions.Logging;
using Plugin.BLE;
using Plugin.BLE.Abstractions;
using Plugin.BLE.Abstractions.Contracts;
using Plugin.BLE.Abstractions.EventArgs;
using System.Diagnostics;

namespace BleTextSender.Services;

public class BleService : IBleService
{
    public BleService(ILogger<BleService> logger)
    {
        _logger = logger;
        _logger.LogInformation("[BLE] BleService erstellt.");

        _ble = CrossBluetoothLE.Current;
        _adapter = _ble.Adapter;

        // Nur EINMAL registrieren
        _adapter.DeviceDiscovered += Adapter_DeviceDiscovered;
    }

    public string? ConnectedDeviceName => _connectedDevice?.Name;

    public async Task<bool> ConnectToDeviceAsync(string deviceId)
    {
        try
        {
            var device = _adapter.DiscoveredDevices.FirstOrDefault(d => d.Id.ToString() == deviceId);
            if (device == null)
            {
                Debug.WriteLine("[BLE] Gerät nicht gefunden.");
                return false;
            }

            await _adapter.ConnectToDeviceAsync(device);
            _connectedDevice = device;

            var services = await _connectedDevice.GetServicesAsync();
            foreach (var service in services)
            {
                var characteristics = await service.GetCharacteristicsAsync();
                _writeCharacteristic = characteristics.FirstOrDefault(c => c.CanWrite);
                if (_writeCharacteristic != null) break;
            }

            return _writeCharacteristic != null;
        }
        catch (Exception ex)
        {
            Debug.WriteLine($"[BLE] Fehler bei Verbindung: {ex.Message}");
            return false;
        }
    }

    public async Task DisconnectAsync()
    {
        if (_connectedDevice != null)
        {
            await _adapter.DisconnectDeviceAsync(_connectedDevice);
            _connectedDevice = null;
        }
    }

    public async Task<bool> SendTextAsync(string message)
    {
        if (_connectedDevice == null)
            return false;

        try
        {
            // Prüfen, ob die Verbindung noch besteht
            if (!_adapter.ConnectedDevices.Any(d => d.Id == _connectedDevice.Id))
            {
                Debug.WriteLine("[BLE] Verbindung verloren – versuche Reconnect…");

                await _adapter.ConnectToDeviceAsync(_connectedDevice, new ConnectParameters(autoConnect: true));

                // Nach erfolgreichem Reconnect: WriteCharacteristic erneut holen
                await RediscoverCharacteristicsAsync();

                Debug.WriteLine("[BLE] Wieder verbunden.");
            }

            if (_writeCharacteristic == null)
            {
                Debug.WriteLine("[BLE] WriteCharacteristic fehlt – keine Übertragung möglich.");
                return false;
            }

            var bytes = System.Text.Encoding.UTF8.GetBytes(message);
            await _writeCharacteristic.WriteAsync(bytes);

            return true;
        }
        catch (Exception ex)
        {
            Debug.WriteLine($"[BLE] Fehler beim Senden/Reconnect: {ex.Message}");
            return false;
        }
    }

    public async Task StartScanningAsync(Action<string, string> onDeviceFound)
    {
        var cts = new CancellationTokenSource(TimeSpan.FromSeconds(5)); // 5s Timeout

        // optional: vor Scan prüfen
        if (_adapter.IsScanning)
            await _adapter.StopScanningForDevicesAsync();

        _adapter.DeviceDiscovered += (s, a) =>
        {
            if (a.Device.Name?.Equals(DEVICE_NAME, StringComparison.OrdinalIgnoreCase) == true)
            {
                onDeviceFound?.Invoke(a.Device.Name, a.Device.Id.ToString());
                _ = _adapter.StopScanningForDevicesAsync();  // sofort abbrechen, async fire-and-forget
            }
        };

        await _adapter.StartScanningForDevicesAsync(
            deviceFilter: d => d.Name?.Equals(DEVICE_NAME, StringComparison.OrdinalIgnoreCase) == true,
            cancellationToken: cts.Token
        );
    }

    public async Task StopScanningAsync()
    {
        if (_adapter.IsScanning)
        {
            _logger.LogInformation("[BLE] Stoppe BLE-Scan.");
            await _adapter.StopScanningForDevicesAsync();
        }

        _onDeviceFound = null;
    }

    private const string DEVICE_NAME = "ESP32_Display";

    private readonly IAdapter _adapter;

    private readonly IBluetoothLE _ble;

    private readonly ILogger<BleService> _logger;

    private IDevice? _connectedDevice;

    private Action<string, string>? _onDeviceFound;

    private ICharacteristic? _writeCharacteristic;

    private void Adapter_DeviceDiscovered(object? sender, DeviceEventArgs args)
    {
        var name = args.Device.Name ?? "Unbekannt";
        var id = args.Device.Id.ToString();

        _logger.LogInformation("[BLE] Gerät entdeckt: {Name} ({Id})", args.Device.Name, args.Device.Id);

        _onDeviceFound?.Invoke(name, id);
    }

    private async Task RediscoverCharacteristicsAsync()
    {
        _writeCharacteristic = null;

        var services = await _connectedDevice!.GetServicesAsync();

        foreach (var service in services)
        {
            var characteristics = await service.GetCharacteristicsAsync();

            foreach (var characteristic in characteristics)
            {
                if (characteristic.CanWrite)
                {
                    _writeCharacteristic = characteristic;
                    return;
                }
            }
        }
    }
}