import { PacketBuilder } from '@/shared/ble/BlePacketBuilder';
import { useBleStore } from '@/shared/store/bleStore';
import log from '@/shared/utils/log';
import { useForm } from 'react-hook-form';
import CalibrationForm from './CalibrationForm';
import NumberField from './NumberField';

interface LineFollowForm {
  crs: string;
  cre: string;
}

export default function LineFollowForm() {
  const send = useBleStore((s) => s.sendAndReceive);
  const { control, handleSubmit } = useForm<LineFollowForm>({
    defaultValues: {
      crs: '0',
      cre: '0.7',
    },
  });

  const handleLineFollower = async (data: LineFollowForm) => {
    await send(PacketBuilder.setCrs(parseFloat(data.crs.replace(',', '.'))), 500).catch(
      (e) => log(e, 'error')
    );
    await send(PacketBuilder.setCre(parseFloat(data.cre.replace(',', '.'))), 500).catch(
      (e) => log(e, 'error')
    );
  };

  return (
    <CalibrationForm
      label="LineFollow"
      handleSubmit={handleSubmit}
      onSubmit={handleLineFollower}>
      <NumberField
        label="crs"
        name="crs"
        rules={{
          min: { value: 0, message: 'Minimum is 0' },
          max: {
            value: 1,
            message: 'Maximum is 1',
          },
        }}
        control={control}
      />
      <NumberField
        label="cre"
        name="cre"
        rules={{
          min: { value: 0, message: 'Minimum is 0' },
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
