import PageContainer from '@/shared/components/ui/PageContainer';
import { useDeviceStore } from '@/shared/store/deviceStore';
import { useForm } from 'react-hook-form';
import CalibrationForm from './components/CalibrationForm';
import NumberField from './components/NumberField';

type CalibrationFormValues = {
  base: string;
  cK: string;
};

export default function CalibrationTab() {
  const setSpeed = useDeviceStore((s) => s.setSpeed);
  const { control, handleSubmit } = useForm<CalibrationFormValues>({
    defaultValues: { base: '200', cK: '0.7' },
  });

  return (
    <PageContainer>
      <CalibrationForm
        handleSubmit={handleSubmit}
        onSubmit={(data) => {
          setSpeed(Number(data.base));
        }}>
        <NumberField
          label="base"
          name="base"
          rules={{
            min: {
              value: 0,
              message: 'Minimum is 0',
            },
            max: {
              value: 255,
              message: 'Maximum is 255',
            },
          }}
          control={control}
        />
        <NumberField
          label="cK"
          name="cK"
          rules={{
            min: {
              value: 0,
              message: 'Minimum is 0',
            },
            max: {
              value: 1,
              message: 'Maximum is 1',
            },
          }}
          control={control}
        />
      </CalibrationForm>
    </PageContainer>
  );
}
