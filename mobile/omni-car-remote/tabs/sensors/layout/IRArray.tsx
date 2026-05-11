import SectionLabel from '@/shared/components/ui/SectionLabel';
import { useEffect, useState } from 'react';
import { Text, View } from 'react-native';
import { useSharedValue, withTiming } from 'react-native-reanimated';
import IRIndicator from '../components/IRIndicator';

export default function IRAarray() {
  const h1 = useSharedValue(2);
  const h2 = useSharedValue(2);
  const h3 = useSharedValue(2);
  const h4 = useSharedValue(2);
  const h5 = useSharedValue(2);
  const sharedValues = [h1, h2, h3, h4, h5];
  const [active, setActive] = useState<boolean[]>([true, false, false, false, true]);

  useEffect(() => {
    active.forEach((isActive, index) => {
      sharedValues[index].value = withTiming(isActive ? 36 : 3, { duration: 100 });
    });
  }, [active]);

  return (
    <View className="mb-[19px]">
      <SectionLabel label="ir array " />
      <View className="bg-surface gap-1 rounded-[10px] px-inlinePadding py-blockPadding ">
        <View className="h-[36px] flex-row gap-[6px]">
          <IRIndicator sharedValue={h1} isActive={active[0]} />
          <IRIndicator sharedValue={h2} isActive={active[1]} />
          <IRIndicator sharedValue={h3} isActive={active[2]} />
          <IRIndicator sharedValue={h4} isActive={active[3]} />
          <IRIndicator sharedValue={h5} isActive={active[4]} />
        </View>
        <View className="flex-row gap[6px]">
          <Text className="text-muted text-center flex-1 font-medium text-[10px]">
            IR1
          </Text>
          <Text className="text-muted text-center flex-1 font-medium text-[10px]">
            IR2
          </Text>
          <Text className="text-muted text-center flex-1 font-medium text-[10px]">
            IR3
          </Text>
          <Text className="text-muted text-center flex-1 font-medium text-[10px]">
            IR4
          </Text>
          <Text className="text-muted text-center flex-1 font-medium text-[10px]">
            IR5
          </Text>
        </View>
      </View>
    </View>
  );
}
