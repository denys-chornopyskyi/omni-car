import { PacketBuilder } from '../BlePacketBuilder';
import { PROTOCOL } from '../types/bleProtocol';
import { SimpleCmd } from '../types/simpleCmd';

describe('BlePacketBuilder', () => {
  afterEach(() => {
    jest.restoreAllMocks();
  });
  // ── Структура пакета ──
  describe('структура пакета', () => {
    it('начинается с START байта', () => {
      const packet = PacketBuilder.stop();
      expect(packet[0]).toBe(PROTOCOL.START);
    });

    it('заканчивается END байтом', () => {
      const packet = PacketBuilder.stop();
      expect(packet[packet.length - 1]).toBe(PROTOCOL.END);
    });

    test('LEN байт соответствует длине payload', () => {
      const packet = PacketBuilder.stop();
      const len = packet[2];
      const total = 1 + 1 + 1 + len + 1;
      expect(packet.length).toBe(total);
    });
  });
  describe('PacketBuilder command methods', () => {
    test('stop() should call build with stop command', () => {
      const spy = jest.spyOn(PacketBuilder, 'build');

      const result = PacketBuilder.stop();

      expect(result[1]).toBe(
        spy.mock.calls[0][2] ? spy.mock.calls[0][0] | 0x80 : spy.mock.calls[0][0]
      );
      expect(result).toEqual(
        new Uint8Array([
          PROTOCOL.START,
          spy.mock.calls[0][2] ? spy.mock.calls[0][0] | 0x80 : spy.mock.calls[0][0],
          spy.mock.calls[0][1].length,
          SimpleCmd.stop,
          PROTOCOL.END,
        ])
      );
    });
  });
});
