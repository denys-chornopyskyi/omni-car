import SectionLabel from '@/shared/components/ui/SectionLabel';
import { View } from 'react-native';
import DistanceItem from '../components/DistanceItem';

export default function Distance() {
  return (
    <View className="mb-[19px]">
      <SectionLabel label="distance" />
      <View className="flex-col gap-buttonGap">
        <View className="flex-row gap-buttonGap">
          <DistanceItem arrowDirection="long-arrow-up" side="Front" />
          <DistanceItem arrowDirection="long-arrow-left" side="Left" />
        </View>
        <View className="flex-row gap-buttonGap">
          <DistanceItem arrowDirection="long-arrow-down" side="Back" />
          <DistanceItem arrowDirection="long-arrow-right" side="Right" />
        </View>
      </View>
    </View>
  );
}
