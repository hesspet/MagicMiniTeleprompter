using CommunityToolkit.Mvvm.Messaging.Messages;

namespace BleTextSender.Messages // oder passender Namespace
{
    public class PermissionsGrantedMessage : ValueChangedMessage<bool>
    {
        public PermissionsGrantedMessage(bool value) : base(value)
        {
        }
    }
}