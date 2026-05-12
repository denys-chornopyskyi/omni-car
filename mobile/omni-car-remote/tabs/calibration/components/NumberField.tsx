import { Control, Controller, FieldValues, Path, RegisterOptions } from 'react-hook-form';
import { Text, TextInput, View } from 'react-native';

type NumberFieldProps<T extends FieldValues> = {
  label: string;
  control: Control<T>;
  rules?: RegisterOptions<T, Path<T>>;
  name: Path<T>;
  placeholder?: string;
};

export default function NumberField<T extends FieldValues>({
  label,
  control,
  rules,
  name,
  placeholder,
}: NumberFieldProps<T>) {
  return (
    <Controller
      control={control}
      rules={{
        required: 'Value is required!!',
        ...rules,
      }}
      name={name}
      render={({ field: { onBlur, onChange, value }, fieldState: { error } }) => (
        <View className="flex-col gap-2">
          <View className="flex-row items-center">
            <Text className="flex-1 text-primary font-medium text-[15px]">{label}</Text>
            <TextInput
              keyboardType="numeric"
              className="bg-black flex-1 border-border border-[2px] pl-1 rounded-[5px] font-medium text-white py-[2px]"
              placeholder={placeholder}
              value={value}
              onBlur={onBlur}
              onChangeText={(text) => {
                let filtered = text.replace(/[^0-9,]/g, '');
                filtered = filtered.length > 4 ? filtered.slice(0, 4) : filtered;
                onChange(filtered);
              }}
            />
          </View>
          {error && (
            <Text className="text-center border-danger border-[2px] rounded-[5px] bg-[#FF3B5C23] py-[2px] px-[2px]  text-danger font-medium text-[15px]">
              {error.message}
            </Text>
          )}
        </View>
      )}
    />
  );
}
