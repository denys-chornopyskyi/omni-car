import { reverseMap } from '../utils/BleHelpers';

export const PROTOCOL = {
  START: 0xaa,
  END: 0xff,
} as const;

export const PacketType = {
  motion: 0x01,
  simpleCmd: 0x02,
  paramCmd: 0x03,
  successResponse: 0x50,
  errorResponse: 0x51,
} as const;

export const PacketTypeReverse = reverseMap<typeof PacketType>(PacketType);

export type PacketTypeValue = (typeof PacketType)[keyof typeof PacketType];

export const responseStatus = {
  Success: 0x50,
  Error: 0x51,
} as const;

export interface SuccessPayload {
  response: Uint8Array;
}

export interface ErrorPayload {
  response: Uint8Array;
}

export interface IRSensorPayload {
  response: Uint8Array;
}

export interface USSensorPayload {
  response: Uint8Array;
}

export const InPacketType = {
  ...responseStatus,
  IRSensor: 0x04,
  USSensor: 0x05,
} as const;

export type InPacketTypeValue = (typeof InPacketType)[keyof typeof InPacketType];

export type InPacketTypePayloadMap = {
  [InPacketType.Success]: SuccessPayload;
  [InPacketType.Error]: ErrorPayload;
  [InPacketType.IRSensor]: IRSensorPayload;
  [InPacketType.USSensor]: USSensorPayload;
};

export enum ValueType {
  uint8 = 1,
  float = 2,
  bool = 3,
}
