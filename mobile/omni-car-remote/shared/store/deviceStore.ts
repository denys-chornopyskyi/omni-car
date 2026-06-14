import { create } from 'zustand';

interface DeviceStore {
  speed: number;
  safetyMode: boolean;
  setSafetyMode: (v: boolean) => void;
  activeMode: 'manual' | 'line' | 'object';
  setActiveMode: (mode: 'manual' | 'line' | 'object') => void;
  setSpeed: (value: number) => void;
  ir: number[];
  setIr: (value: number[]) => void;
  threshold: number;
  setThreshold: (value: number) => void;
  forwardSensor: number;
  backwardSensor: number;
  leftSensor: number;
  rightSensor: number;
  setSensors: (fs: number, bs: number, ls: number, rs: number) => void;
}

export const useDeviceStore = create<DeviceStore>((set, get) => ({
  safetyMode: false,
  setSafetyMode: (v) => set({ safetyMode: v }),
  speed: 100,
  setSpeed: (value) => set({ speed: value }),
  ir: [1, 0, 0, 0, 0],
  setIr: (value) => set({ ir: [...value] }),
  activeMode: 'manual',
  setActiveMode: (value) => set({ activeMode: value }),
  threshold: 0,
  setThreshold: (value) => set({ threshold: value }),
  forwardSensor: 0,
  backwardSensor: 0,
  leftSensor: 0,
  rightSensor: 0,
  setSensors: (fs, bs, ls, rs) =>
    set({
      forwardSensor: fs,
      backwardSensor: bs,
      leftSensor: ls,
      rightSensor: rs,
    }),
}));
