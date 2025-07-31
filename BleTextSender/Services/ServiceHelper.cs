namespace BleTextSender.Services;

public static class ServiceHelper
{
    public static IServiceProvider? ServiceProvider { get; set; }

    /// <summary>
    /// Populates the static ServiceHelper with the service provider.
    /// </summary>
    public static T GetService<T>() where T : notnull
        => ServiceProvider!.GetRequiredService<T>();
}