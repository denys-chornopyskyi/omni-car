import SectionLabel from '@/shared/components/ui/SectionLabel';
import { useDeviceStore } from '@/shared/store/deviceStore';
import { View } from 'react-native';
import SafetyGuardItem from '../components/SafetyGuardItem';

export default function SafetyGuard() {
  const fs = useDeviceStore((s) => s.forwardSensor);
  const bs = useDeviceStore((s) => s.backwardSensor);
  const ls = useDeviceStore((s) => s.leftSensor);
  const rs = useDeviceStore((s) => s.rightSensor);
  const threshold = useDeviceStore((s) => s.threshold);

  return (
    <View className="mb-[19px]">
      <SectionLabel label="safety guard" />
      <View className="flex-row gap-[6px]">
        <SafetyGuardItem
          side="Front"
          arrowDirection="long-arrow-up"
          isClear={fs > threshold}
        />
        <SafetyGuardItem
          side="Back"
          arrowDirection="long-arrow-down"
          isClear={bs > threshold}
        />
        <SafetyGuardItem
          side="Left"
          arrowDirection="long-arrow-left"
          isClear={ls > threshold}
        />
        <SafetyGuardItem
          side="Right"
          arrowDirection="long-arrow-right"
          isClear={rs > threshold}
        />
      </View>
    </View>
  );
}
