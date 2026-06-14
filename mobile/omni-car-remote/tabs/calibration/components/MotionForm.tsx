import { PacketBuilder } from '@/shared/ble/BlePacketBuilder';
import { useBleStore } from '@/shared/store/bleStore';
import log from '@/shared/utils/log';
import { useForm } from 'react-hook-form';
import CalibrationForm from './CalibrationForm';
import NumberField from './NumberField';

type MotionFormValues = {
  base: string;
  cK: string;
};

export default function MotionForm() {
  const send = useBleStore((s) => s.sendAndReceive);
  const { control, handleSubmit } = useForm<MotionFormValues>({
    defaultValues: { base: '200', cK: '0.7' },
  });

  const handleMotion = async (data: MotionFormValues) => {
    console.log('CK: ', parseFloat(data.cK.replace(',', '.')));
    await send(PacketBuilder.setBase(parseInt(data.base, 10)), 500).catch((e) =>
      log(e, 'error')
    );
    await send(PacketBuilder.setCK(parseFloat(data.cK.replace(',', '.'))), 500).catch(
      (e) => log(e, 'error')
    );
  };

  return (
    <CalibrationForm
      label="Motion"
      handleSubmit={handleSubmit}
      onSubmit={(data) => handleMotion(data)}>
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
  );
}
