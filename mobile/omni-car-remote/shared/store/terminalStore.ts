import { create } from 'zustand';

export type LogEntry = {
  id: string;
  message: string;
  type: 'info' | 'error' | 'success';
  timestamp: Date;
};

export type TerminalStore = {
  logs: LogEntry[];
  addLog: (message: string, type?: LogEntry['type']) => void;
  clearLogs: () => void;
};

export const useTerminalStore = create<TerminalStore>((set) => ({
  logs: [],

  addLog: (message, type = 'info') =>
    set((state) => ({
      logs: [
        ...state.logs,
        {
          id: Date.now().toString() + Math.random().toString(),
          message,
          timestamp: new Date(),
          type,
        },
      ],
    })),

  clearLogs: () => set({ logs: [] }),
}));
