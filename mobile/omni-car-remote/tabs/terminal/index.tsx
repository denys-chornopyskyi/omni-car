import PageContainer from '@/shared/components/ui/PageContainer';
import { useBleStore } from '@/shared/store/bleStore';
import { useTerminalStore } from '@/shared/store/terminalStore';
import { useState } from 'react';
import { View } from 'react-native';
import TerminalFooter from './components/TerminalFooter';
import TerminalHeader from './components/TerminalHeader';
import TerminalMain from './components/TerminalMain';
import QuickCommands from './layout/QuickCommands';

export default function TerminalTab() {
  const [focus, setFocus] = useState(false);
  const { logs, addLog, clearLogs } = useTerminalStore();
  const { send } = useBleStore();
  const [command, setCommand] = useState('');

  const handleSend = async () => {
    addLog(command);
    await send(command);
    setCommand('');
  };

  return (
    <PageContainer>
      <View>
        <TerminalHeader clearLogs={clearLogs} />
        <TerminalMain logs={logs} focus={focus} />
        <TerminalFooter
          onSend={handleSend}
          onFocus={setFocus}
          command={command}
          onChangeText={setCommand}
        />
      </View>
      <QuickCommands onSelect={setCommand} />
    </PageContainer>
  );
}
