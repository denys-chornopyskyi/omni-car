import { reverseMap } from '../utils/BleHelpers';

export const SimpleCmd = {
  stop: 1,
  'base?': 2,
  'cK?': 10,
  'module:manual': 3,
  'module:line': 4,
  // safetymode: 5,
  'safetymode?': 14,
  'module?': 15,
  // 'kA?': 6,
  // 'kB?': 7,
  // 'kC?': 8,
  // 'kD?': 9,
  'threshold?': 11,
  'crs?': 12,
  'cre?': 13,
  sIRs: 16,
  eIRs: 17,
  sUSs: 18,
  eUSs: 19,
  startLine: 20,
  endLine: 21,
  'module:object': 22,
  startFollowing: 23,
  stopFollowing: 24,
  'minDist?': 25,
  'maxDist?': 26,
} as const;

export const SimpleCmdReverse = reverseMap<typeof SimpleCmd>(SimpleCmd);
export type SimpleCmdValue = (typeof SimpleCmd)[keyof typeof SimpleCmd];
