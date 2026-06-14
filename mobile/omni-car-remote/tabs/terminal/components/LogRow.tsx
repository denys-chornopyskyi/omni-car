import { LogEntry } from '@/shared/store/terminalStore';
import { Text, View } from 'react-native';

const TYPE_COLOR = {
  info: 'text-primary',
  error: 'text-danger',
  success: 'text-neonGreen',
};

export default function LogRow({ item }: { item: LogEntry }) {
  const time = item.timestamp.toLocaleTimeString('cs', {
    hour: '2-digit',
    minute: '2-digit',
    second: '2-digit',
  });

  return (
    <View className="flex-row gap-2 py-[2px]">
      <Text className="text-muted text-[14px] font-semibold">{time}</Text>
      <Text className={`${TYPE_COLOR[item.type]} text-[14px] font-semibold flex-1`}>
        {item.message}
      </Text>
    </View>
  );
}
