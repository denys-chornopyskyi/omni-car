import SectionLabel from '@/shared/components/ui/SectionLabel';
import { View } from 'react-native';
import QuickCommand from '../components/QuickCommand';

export default function QuickCommands({ onSelect }: { onSelect: (cmd: string) => void }) {
  return (
    <View className=" flex-col mt-5">
      <View>
        <SectionLabel label="Quick Commands" />
      </View>
      <View className="flex-row gap-buttonGap flex-wrap">
        <QuickCommand label="base?" onPress={() => onSelect('base?')} />
        <QuickCommand label="base:200" onPress={() => onSelect('base:200')} />
        <QuickCommand label="sUSs" onPress={() => onSelect('sUSs')} />
        <QuickCommand label="eUSs" onPress={() => onSelect('eUSs')} />
        <QuickCommand label="sIRs" onPress={() => onSelect('sIRs')} />
        <QuickCommand label="eIRs" onPress={() => onSelect('eIRs')} />
        <QuickCommand label="safetymode?" onPress={() => onSelect('safetymode?')} />
        <QuickCommand label="minDist?" onPress={() => onSelect('minDist?')} />
        <QuickCommand label="maxDist?" onPress={() => onSelect('maxDist?')} />
        <QuickCommand label="crs?" onPress={() => onSelect('crs')} />
        <QuickCommand label="cre?" onPress={() => onSelect('cre?')} />
        <QuickCommand label="ck?" onPress={() => onSelect('cK?')} />
      </View>
    </View>
  );
}
