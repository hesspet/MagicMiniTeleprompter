namespace BleTextSender.Services;

public static class ServiceHelper
{
    public static IServiceProvider? ServiceProvider { get; set; }

    public static T GetService<T>() where T : notnull
        => ServiceProvider!.GetRequiredService<T>();
}