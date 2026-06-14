import PageContainer from '@/shared/components/ui/PageContainer';
import { useBleStore } from '@/shared/store/bleStore';
import { useTerminalStore } from '@/shared/store/terminalStore';
import { useCallback, useState } from 'react';
import { View } from 'react-native';
import TerminalFooter from './components/TerminalFooter';
import TerminalHeader from './components/TerminalHeader';
import TerminalMain from './components/TerminalMain';
import { TextCommandParser } from './components/utils/TextCommandParser';
import QuickCommands from './layout/QuickCommands';

export default function TerminalTab() {
  const [focus, setFocus] = useState(false);
  const { logs, addLog, clearLogs } = useTerminalStore();
  const { sendAndReceive, send } = useBleStore();
  const [command, setCommand] = useState('');

  const bleSend = useCallback(async (cmd: string) => {
    const trimmed = cmd.trim();
    if (!trimmed) return;

    addLog(`→ sent ${trimmed}`, 'info');

    const result = TextCommandParser.parse(trimmed);
    if (!result) {
      addLog(`← unknown command: ${trimmed}`, 'error');
      return;
    }

    try {
      if (true) {
        const response = await sendAndReceive(result, 10000);
        addLog(`← ok: ${response.value}`, 'success');
      } else {
      }
    } catch (err) {
      addLog(`${String(err)}`, 'error');
    }
  }, []);

  const handleSend = async () => {
    bleSend(command);
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
