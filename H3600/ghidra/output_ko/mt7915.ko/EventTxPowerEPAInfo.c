// module: mt7915.ko
// function: EventTxPowerEPAInfo @ 0x1a8098
// size: 20 bytes
//

void EventTxPowerEPAInfo(int param_1,int param_2)

{
  *(undefined1 *)(param_1 + 0x285a2c) = *(undefined1 *)(param_2 + 1);
  return;
}

