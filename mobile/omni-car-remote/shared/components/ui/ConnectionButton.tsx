import { useBleStore } from '@/shared/store/bleStore';
import cn from '@/shared/utils/cn';
import Button from './Button';

export default function ConnectionButton() {
  const { connect, connected, scanning, disconnect } = useBleStore();

  const labelMap = {
    idle: 'connect',
    connecting: 'connecting',
    connected: 'disconnect',
  } as const;

  const status = connected ? 'connected' : scanning ? 'connecting' : 'idle';

  return (
    <Button
      label={labelMap[status]}
      variant="custom"
      onPress={() => (connected ? disconnect() : connect())}
      className={cn(
        'px-6 rounded-full',
        connected && 'border-neonGreen',
        !connected && 'border-neonRed',
        scanning && 'border-[#C77DFF65]'
      )}
    />
  );
}
