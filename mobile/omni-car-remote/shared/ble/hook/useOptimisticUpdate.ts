import log from '@/shared/utils/log';

export const useOptimisticUpdate = () => {
  const update = async <T>(
    getter: () => T,
    setter: (value: T) => void,
    newValue: T,
    request: () => Promise<void>
  ) => {
    const previous = getter();

    setter(newValue);

    try {
      await request();
    } catch (e: any) {
      log(e, 'error');
      setter(previous);
    }
  };

  return { update };
};
