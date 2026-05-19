export const PROTOCOL = {
  START: 0xaa,
  END: 0xff,
} as const;

export const PacketType = {
  motion: 0x01,
  cmd: 0x02,
} as const;

export type PacketTypeValue = (typeof PacketType)[keyof typeof PacketType];
