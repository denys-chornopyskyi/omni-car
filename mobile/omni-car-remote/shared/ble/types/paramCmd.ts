import { reverseMap } from '../utils/BleHelpers';
export const ParamCmd = {
  base: 1,
  // kA: 2,
  // kB: 3,
  // kC: 4,
  // kD: 5,
  cK: 6,
  // mA: 7,
  // mB: 8,
  // mC: 9,
  // mD: 10,
  threshold: 11,
  minDist: 12,
  maxDist: 13,
  safetymode: 14,
  crs: 15,
  cre: 16,
  radius: 17,
} as const;

export const ModuleType = {
  manual: 1,
  line: 2,
} as const;

export type ParamCmdValue = (typeof ParamCmd)[keyof typeof ParamCmd];

export const ParamTypeReverse = reverseMap<typeof ParamCmd>(ParamCmd);
