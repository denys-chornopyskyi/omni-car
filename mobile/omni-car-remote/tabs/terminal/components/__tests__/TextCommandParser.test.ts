import { PacketBuilder } from '@/shared/ble/BlePacketBuilder';
import { TextCommandParser } from '../utils/TextCommandParser';

describe('TextCommandParser', () => {
  describe('Simple commands', () => {
    afterEach(() => {
      jest.restoreAllMocks();
    });

    const cases = [
      ['base?', 'getBase'],
      ['stop', 'stop'],
      ['module:manual', 'setManualModule'],
      ['module:line', 'setLineModule'],
      ['module?', 'getModule'],
      ['cK?', 'getCK'],
      ['safetymode?', 'getSafetyMode'],
      ['safetymode', 'toggleSafetyMode'],
      ['cre?', 'getCre'],
      ['crs?', 'getCrs'],
      ['threshold?', 'getThreshold'],
      ['sIRs', 'startIRstream'],
      ['eIRs', 'endIRstream'],
      ['sUSs', 'startUSstream'],
      ['eUSs', 'endUSstream'],
      ['cK:10', 'setCK'],
      ['base:10', 'setBase'],
      ['threshold:10', 'setThreshold'],
    ] as const;

    it.each(cases)('%s should call %s', (commandName, methodName) => {
      const mockPacket = new Uint8Array([1, 2, 3]);

      const spy = jest.spyOn(PacketBuilder, methodName).mockReturnValue(mockPacket);

      const result = TextCommandParser.parse(commandName);

      expect(spy).toHaveBeenCalledTimes(1);
      expect(result).toBe(mockPacket);
    });

    test('invalid command should return null', () => {
      const invalidCommand = 'wrongCommand';

      const result = TextCommandParser.parse(invalidCommand);
      expect(result).toBeNull();
    });
    test('invalid command should return null', () => {
      const invalidCommand = 'wrong:Command';

      const result = TextCommandParser.parse(invalidCommand);
      expect(result).toBeNull();
    });
  });
});
