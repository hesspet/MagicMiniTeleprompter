using BleTextSender.Services;
using CommunityToolkit.Maui;
using Microsoft.Extensions.Logging;

namespace BleTextSender;

public static class MauiProgram
{
    public static MauiApp CreateMauiApp()
    {
        var builder = MauiApp.CreateBuilder();
        builder
            .UseMauiApp<App>()
            .UseMauiCommunityToolkit()
            .ConfigureFonts(fonts =>
            {
                fonts.AddFont("OpenSans-Regular.ttf", "OpenSansRegular");
                fonts.AddFont("OpenSans-Semibold.ttf", "OpenSansSemibold");
            });

#if DEBUG
        builder.Logging.AddDebug();
        builder.Logging.AddConsole();
        builder.Logging.SetMinimumLevel(LogLevel.Debug);
#endif
        builder.Services.AddSingleton<IBleService, BleService>();

        var serviceProvider = builder.Services.BuildServiceProvider();
        ServiceHelper.ServiceProvider = serviceProvider;

        return builder.Build();
    }
}