import Button from '@/shared/components/ui/Button';
import { TerminalStore } from '@/shared/store/terminalStore';
import { Text, View } from 'react-native';

type TerminalHeaderProps = {
  clearLogs: TerminalStore['clearLogs'];
};

export default function TerminalHeader({ clearLogs }: TerminalHeaderProps) {
  return (
    <View className="bg-surface border border-border px-inlinePadding justify-between flex-row items-center py-[10px] rounded-t-[10px]">
      <Text className="text-muted font-semibold text-[12px]">//SERIAL LOG</Text>
      <Button
        label="clear"
        variant="custom"
        className="border-transparent py-0"
        textClass="text-muted text-[12px] font-semibold"
        onPress={clearLogs}
      />
    </View>
  );
}
