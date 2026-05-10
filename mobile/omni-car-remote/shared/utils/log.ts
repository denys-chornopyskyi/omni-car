import { LogEntry, useTerminalStore } from '../store/terminalStore';

export default function log(msg: string, type: LogEntry['type'] = 'info'): void {
  console.log(msg);
  useTerminalStore.getState().addLog(msg, type);
}
