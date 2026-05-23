// module: mt7915.ko
// function: EventTxPowerCompTable @ 0x1a879c
// size: 52 bytes
//

void EventTxPowerCompTable(int param_1,int param_2)

{
  if (1 < *(byte *)(param_2 + 1)) {
    return;
  }
  os_move_mem((void *)(param_1 + (uint)*(byte *)(param_2 + 1) * 0xc4 + 0x794ead),
              (void *)(param_2 + 4),0xc4);
  return;
}

