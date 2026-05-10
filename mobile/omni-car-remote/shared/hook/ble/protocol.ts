const CMD_TYPE = {
  SPEED: 0x01,
  MOTION: 0x02,
  CMD: 0x03,
};

export function parsePacket(data: Uint8Array) {
  const type = data[0];
  const value = data[1];

  switch (type) {
    case CMD_TYPE.SPEED:
      return { type: 'speed', value: value };
    default:
      return null;
  }
}

export function buildPacket(type: number, value: number): Uint8Array {
  return new Uint8Array([type, value]);
}
