import Button from '@/shared/components/ui/Button';
import SectionLabel from '@/shared/components/ui/SectionLabel';
import log from '@/shared/utils/log';
import { useState } from 'react';
import { FieldValues, UseFormHandleSubmit } from 'react-hook-form';
import { View } from 'react-native';

type CalibrationFormProps<T extends FieldValues> = {
  label: string;
  handleSubmit: UseFormHandleSubmit<T>;
  onSubmit?: (data: T) => void;
  children: React.ReactNode;
};

export default function CalibrationForm<T extends FieldValues>({
  label,
  handleSubmit,
  onSubmit,
  children,
}: CalibrationFormProps<T>) {
  const [isSent, setSend] = useState(false);

  const handleLocalSubmit = (data: any) => {
    onSubmit?.(data);

    log(JSON.stringify(data));

    setSend(true);
    setTimeout(() => setSend(false), 500);
  };
  return (
    <View className="bg-surface px-inlinePadding py-blockPadding h-max w-[45%] rounded-[10px]">
      <SectionLabel label={label} />
      <View className="gap-2 mb-[9px]">{children}</View>
      <Button
        label={isSent ? 'Sent!' : 'Send'}
        state="selected"
        variant="primary"
        className={isSent ? 'border-neonGreen' : ''}
        textClass={isSent ? 'text-neonGreen' : ''}
        onPress={handleSubmit(handleLocalSubmit)}
      />
    </View>
  );
}
