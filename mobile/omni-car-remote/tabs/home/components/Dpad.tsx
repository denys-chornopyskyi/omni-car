import { PacketBuilder } from '@/ble/BlePacketBuilder';
import { ButtonState, MotionButton } from '@/ble/types/motion';
import { useBleStore } from '@/shared/store/bleStore';
import { useCallback } from 'react';
import { View } from 'react-native';
import DpadButton from './DpadButton';

export default function Dpad() {
  const bleSend = useBleStore((s) => s.send);

  const send = useCallback(
    (btn: keyof typeof MotionButton, state: keyof typeof ButtonState) =>
      bleSend(PacketBuilder.buildMotionPacket(btn, state)),
    []
  );

  return (
    <View className="flex-col gap-5 items-center py-20">
      <View className="flex-row gap-5">
        <DpadButton
          rotation={7}
          onPressIn={() => send('UpLeft', 'Pressed')}
          onPressOut={() => send('UpLeft', 'Released')}
        />
        <DpadButton
          rotation={0}
          onPressIn={() => send('Up', 'Pressed')}
          onPressOut={() => send('Up', 'Released')}
        />
        <DpadButton
          rotation={1}
          onPressIn={() => send('UpRight', 'Pressed')}
          onPressOut={() => send('UpRight', 'Released')}
        />
      </View>
      <View className="flex-row gap-5">
        <DpadButton
          rotation={6}
          onPressIn={() => send('Left', 'Pressed')}
          onPressOut={() => send('Left', 'Released')}
        />
        <DpadButton
          dot
          onPressIn={() => send('Center', 'Pressed')}
          onPressOut={() => send('Center', 'Released')}
        />
        <DpadButton
          rotation={2}
          onPressIn={() => send('Right', 'Pressed')}
          onPressOut={() => send('Right', 'Released')}
        />
      </View>
      <View className="flex-row gap-5">
        <DpadButton
          rotation={5}
          onPressIn={() => send('DownLeft', 'Pressed')}
          onPressOut={() => send('DownLeft', 'Released')}
        />
        <DpadButton
          rotation={4}
          onPressIn={() => send('Down', 'Pressed')}
          onPressOut={() => send('Down', 'Released')}
        />
        <DpadButton
          rotation={3}
          onPressIn={() => send('DownRight', 'Pressed')}
          onPressOut={() => send('DownRight', 'Released')}
        />
      </View>
    </View>
  );
}
