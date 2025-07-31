using CommunityToolkit.Maui.Alerts;
using CommunityToolkit.Maui.Core;

namespace BleTextSender.Helpers;

public static class Notifier
{
    /// <summary>
    /// Zeigt eine deutlich sichtbare Fehlermeldung (Snackbar) mit rotem Hintergrund.
    /// </summary>
    public static async Task ShowErrorAsync(string message)
    {
        var snackbar = Snackbar.Make(
            message,
            action: () => { }, // Keine Aktion, kann auch null sein
            actionButtonText: string.Empty,
            duration: TimeSpan.FromSeconds(3),
            visualOptions: new SnackbarOptions
            {
                BackgroundColor = Colors.DarkRed,
                TextColor = Colors.Yellow,
                CornerRadius = 8
            });

        await snackbar.Show();
    }

    /// <summary>
    /// Zeigt eine dezente Textmeldung (Toast) am unteren Bildschirmrand.
    /// </summary>
    public static async Task ShowToastAsync(string message)
    {
        var toast = Toast.Make(message, ToastDuration.Short, 14);
        await toast.Show();
    }
}