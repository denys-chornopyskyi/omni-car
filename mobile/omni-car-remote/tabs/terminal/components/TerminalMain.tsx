import { TerminalStore } from '@/shared/store/terminalStore';
import cn from '@/shared/utils/cn';
import { useRef } from 'react';
import { FlatList } from 'react-native';
import LogRow from './LogRow';

type TerminalMainProps = {
  logs: TerminalStore['logs'];
  focus: boolean;
};

export default function TerminalMain({ logs, focus }: TerminalMainProps) {
  const listRef = useRef<FlatList>(null);

  return (
    <FlatList
      ref={listRef}
      data={logs}
      keyExtractor={(item) => item.id}
      renderItem={({ item }) => <LogRow item={item} />}
      className={cn(
        `bg-[#050011]  border-border px-inlinePadding py-[10px]  border-r border-l`,
        focus ? 'h-[180px]' : 'h-[210px]'
      )}
      onContentSizeChange={() => listRef.current?.scrollToEnd({ animated: true })}
    />
  );
}
