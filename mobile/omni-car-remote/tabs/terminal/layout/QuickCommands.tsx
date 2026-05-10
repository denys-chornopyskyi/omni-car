import SectionLabel from '@/shared/components/ui/SectionLabel';
import { View } from 'react-native';
import QuickCommand from '../components/QuickCommand';

export default function QuickCommands({ onSelect }: { onSelect: (cmd: string) => void }) {
  return (
    <View className=" flex-col mt-5">
      <View>
        <SectionLabel label="Quick Commands" />
      </View>
      <View className="flex-row gap-buttonGap">
        <QuickCommand label="speed?" onPress={() => onSelect('speed?')} />
        <QuickCommand label="speed:200" onPress={() => onSelect('speed:200')} />
      </View>
    </View>
  );
}
