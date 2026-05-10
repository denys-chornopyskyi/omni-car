import Button from '@/shared/components/ui/Button';

export default function QuickCommand({
  label,
  onPress,
}: {
  label: string;
  onPress: () => void;
}) {
  return (
    <Button
      label={label}
      variant="custom"
      onPress={onPress}
      className="bg-surface border-border px-[9px] py-1"
      textClass="text-secondary font-semibold"
    />
  );
}
