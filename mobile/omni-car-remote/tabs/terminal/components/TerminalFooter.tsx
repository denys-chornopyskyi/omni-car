import Button from '@/shared/components/ui/Button';
import { Text, TextInput, View } from 'react-native';

type TerminalFooterProps = {
  onFocus: (focus: boolean) => void;
  command: string;
  onChangeText: (text: string) => void;
  onSend: () => void;
};

export default function TerminalFooter({
  onFocus,
  command,
  onChangeText,
  onSend,
}: TerminalFooterProps) {
  return (
    <View className="bg-panel items-center flex-row border border-border py-[10px] px-inlinePadding rounded-b-[10px]">
      <Text className="mr-[6px] text-primary font-bold">$</Text>
      <TextInput
        placeholder="Commands"
        placeholderTextColor="white"
        className="text-white text-[12px] flex-1"
        onFocus={() => onFocus(true)}
        onBlur={() => onFocus(false)}
        value={command}
        onChangeText={(text) => onChangeText(text)}
        autoCapitalize="none"
        autoCorrect={false}
      />
      <Button
        label="send"
        variant="custom"
        className="border-transparent py-0"
        textClass="font-semibold text-[12px] text-primary"
        onPress={onSend}
      />
    </View>
  );
}
