using Android;
using Android.App;
using Android.Content.PM;
using Android.OS;
using Android.Runtime;
using AndroidX.Core.App;
using AndroidX.Core.Content;

namespace BleTextSender;

[Activity(
    Theme = "@style/Maui.SplashTheme",
    MainLauncher = true,
    LaunchMode = LaunchMode.SingleTop,
    ConfigurationChanges = ConfigChanges.ScreenSize | ConfigChanges.Orientation | ConfigChanges.UiMode |
                           ConfigChanges.ScreenLayout | ConfigChanges.SmallestScreenSize | ConfigChanges.Density)]
public partial class MainActivity : MauiAppCompatActivity
{
    public override void OnRequestPermissionsResult(int requestCode, string[] permissions, [GeneratedEnum] Permission[] grantResults)
    {
        base.OnRequestPermissionsResult(requestCode, permissions, grantResults);

        if (requestCode == 1001 &&
            grantResults.All(r => r == Permission.Granted))
        {
            Console.WriteLine("[BLE][MainActivity] Berechtigung erteilt – sende Nachricht.");
        }
        else
        {
            Console.WriteLine("[BLE][MainActivity] Berechtigung verweigert.");
        }
    }

    protected override void OnCreate(Bundle? savedInstanceState)
    {
        base.OnCreate(savedInstanceState);

        // Prüfe und fordere Berechtigungen zur Laufzeit an
        RequestBlePermissionsIfNeeded();
    }

    private const int RequestId = 1001;

    private void RequestBlePermissionsIfNeeded()
    {
        var permissions = new List<string>();

        if (Build.VERSION.SdkInt >= BuildVersionCodes.S) // Android 12+
        {
            if (ContextCompat.CheckSelfPermission(this, Manifest.Permission.BluetoothScan) != Permission.Granted)
                permissions.Add(Manifest.Permission.BluetoothScan);

            if (ContextCompat.CheckSelfPermission(this, Manifest.Permission.BluetoothConnect) != Permission.Granted)
                permissions.Add(Manifest.Permission.BluetoothConnect);
        }
        else
        {
            if (ContextCompat.CheckSelfPermission(this, Manifest.Permission.Bluetooth) != Permission.Granted)
                permissions.Add(Manifest.Permission.Bluetooth);

            if (ContextCompat.CheckSelfPermission(this, Manifest.Permission.BluetoothAdmin) != Permission.Granted)
                permissions.Add(Manifest.Permission.BluetoothAdmin);
        }

        if (ContextCompat.CheckSelfPermission(this, Manifest.Permission.AccessFineLocation) != Permission.Granted)
            permissions.Add(Manifest.Permission.AccessFineLocation);

        if (permissions.Any())
        {
            ActivityCompat.RequestPermissions(this, permissions.ToArray(), RequestId);
        }
    }
}