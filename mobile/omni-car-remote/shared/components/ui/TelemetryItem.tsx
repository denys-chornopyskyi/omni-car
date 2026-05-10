import { Text, View } from 'react-native';

export type TelemetryItemProps = {
  label: string;
  value: string;
};

const TelemetryItem = ({ label, value }: TelemetryItemProps) => {
  return (
    <View className="flex flex-col flex-1 py-[10px] border-border border-[1px] bg-surface">
      <Text className="color-primary text-[14px] font-mono text-center">
        {value.toUpperCase()}
      </Text>
      <Text className="color-muted text-[8px] font-medium text-center">
        {label.toUpperCase()}
      </Text>
    </View>
  );
};

export default TelemetryItem;
