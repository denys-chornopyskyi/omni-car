import SectionLabel from '@/shared/components/ui/SectionLabel';
import { View } from 'react-native';
import SafetyGuardItem from '../components/SafetyGuardItem';

export default function SafetyGuard() {
  return (
    <View className="mb-[19px]">
      <SectionLabel label="safety guard" />
      <View className="flex-row gap-[6px]">
        <SafetyGuardItem side="Front" arrowDirection="long-arrow-up" isClear={true} />
        <SafetyGuardItem side="Back" arrowDirection="long-arrow-down" isClear={true} />
        <SafetyGuardItem side="Left" arrowDirection="long-arrow-left" isClear={true} />
        <SafetyGuardItem side="Right" arrowDirection="long-arrow-right" isClear={true} />
      </View>
    </View>
  );
}
