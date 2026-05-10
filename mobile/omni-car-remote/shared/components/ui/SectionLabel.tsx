import { Text } from 'react-native';

export default function SectionLabel({ label }: { label: string }) {
  return (
    <Text className="mb-labelSpacing text-[9px] color-muted font-medium">
      {label.toUpperCase()}
    </Text>
  );
}
