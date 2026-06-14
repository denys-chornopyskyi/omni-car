import { PacketBuilder } from '@/shared/ble/BlePacketBuilder';
import { useBleStore } from '@/shared/store/bleStore';
import log from '@/shared/utils/log';
import { useForm } from 'react-hook-form';
import CalibrationForm from './CalibrationForm';
import NumberField from './NumberField';

interface ObjectFollowerFormValues {
  minDist: string;
  maxDist: string;
}

export default function ObjectFollowerForm() {
  const send = useBleStore((s) => s.sendAndReceive);
  const { control, handleSubmit } = useForm<ObjectFollowerFormValues>({
    defaultValues: {
      maxDist: '22',
      minDist: '10',
    },
  });

  const handleObjectFollower = async (data: ObjectFollowerFormValues) => {
    await send(PacketBuilder.setMinDist(parseInt(data.minDist, 10)), 500).catch((e) =>
      log(e, 'error')
    );
    await send(PacketBuilder.setMaxDist(parseInt(data.maxDist, 10)), 500).catch((e) =>
      log(e, 'error')
    );
  };

  return (
    <CalibrationForm
      label="ObjectFollower"
      handleSubmit={handleSubmit}
      onSubmit={handleObjectFollower}>
      <NumberField
        label="minDist"
        name="minDist"
        rules={{
          min: { value: 1, message: 'Minimum is 1' },
          max: {
            value: 100,
            message: 'Maximum is 255',
          },
        }}
        control={control}
      />
      <NumberField
        label="maxDist"
        name="maxDist"
        rules={{
          min: { value: 1, message: 'Minimum is 1' },
          max: {
            value: 100,
            message: 'Maximum is 255',
          },
        }}
        control={control}
      />
    </CalibrationForm>
  );
}
