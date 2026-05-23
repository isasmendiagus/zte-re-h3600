// module: mt7915.ko
// function: EventRxvHandler @ 0x1a8de4
// size: 16 bytes
//

void EventRxvHandler(undefined4 param_1,char *param_2)

{
  if (*param_2 != '\0') {
    return;
  }
  EventRxvReport();
  return;
}

