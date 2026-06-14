import SectionLabel from '@/shared/components/ui/SectionLabel';
import { useDeviceStore } from '@/shared/store/deviceStore';
import { View } from 'react-native';
import DistanceItem from '../components/DistanceItem';

export default function Distance() {
  const fs = useDeviceStore((s) => s.forwardSensor);
  const bs = useDeviceStore((s) => s.backwardSensor);
  const ls = useDeviceStore((s) => s.leftSensor);
  const rs = useDeviceStore((s) => s.rightSensor);

  return (
    <View className="mb-[19px]">
      <SectionLabel label="distance" />
      <View className="flex-col gap-buttonGap">
        <View className="flex-row gap-buttonGap">
          <DistanceItem arrowDirection="long-arrow-up" side="Front" value={fs} />
          <DistanceItem arrowDirection="long-arrow-left" side="Left" value={ls} />
        </View>
        <View className="flex-row gap-buttonGap">
          <DistanceItem arrowDirection="long-arrow-down" side="Back" value={bs} />
          <DistanceItem arrowDirection="long-arrow-right" side="Right" value={rs} />
        </View>
      </View>
    </View>
  );
}
