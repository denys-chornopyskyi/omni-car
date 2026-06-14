import { PacketBuilder } from '@/shared/ble/BlePacketBuilder';
import { useOptimisticUpdate } from '@/shared/ble/hook/useOptimisticUpdate';
import { useBleStore } from '@/shared/store/bleStore';
import { useDeviceStore } from '@/shared/store/deviceStore';
import Slider from '@react-native-community/slider';
import { useCallback, useEffect } from 'react';
import { Text, View } from 'react-native';
import { useDebounce } from 'use-debounce';

export default function SpeedSlider() {
  const speed = useDeviceStore((s) => s.speed);
  const setSpeed = useDeviceStore((s) => s.setSpeed);
  const send = useBleStore((s) => s.sendAndReceive);
  const [debounceSpeed] = useDebounce(speed, 300);
  const { update } = useOptimisticUpdate();

  // const lastConfirmedSpeed = useRef(speed);

  // const sendSpeed = async (speed: number) => {
  //   try {
  //     await send(PacketBuilder.setBase(speed), 500);
  //     lastConfirmedSpeed.current = speed;
  //   } catch (e: any) {
  //     log(e, 'error');
  //     setSpeed(lastConfirmedSpeed.current);
  //   }
  // };
  const handleSpeedChange = useCallback(() => {
    update(
      () => useDeviceStore.getState().speed,
      (v) => useDeviceStore.getState().setSpeed(v),
      debounceSpeed,
      () => send(PacketBuilder.setBase(debounceSpeed), 500)
    );
  }, [debounceSpeed]);

  useEffect(() => {
    // sendSpeed(debounceSpeed);
    handleSpeedChange();
  }, [handleSpeedChange]);

  return (
    <View className="flex-row items-center gap-2 mb-sectionSpacing ">
      <Text className="text-[14px] font-mono color-secondary">Speed</Text>
      <View className="flex-1">
        <Slider
          minimumValue={0}
          maximumValue={255}
          value={speed}
          step={1}
          onValueChange={(v) => setSpeed(v)}
          thumbTintColor="#38BDF8"
          minimumTrackTintColor="#334155"
          maximumTrackTintColor="#334155"
        />
      </View>
      <Text className=" text-primary font-mono">{speed}</Text>
    </View>
  );
}
