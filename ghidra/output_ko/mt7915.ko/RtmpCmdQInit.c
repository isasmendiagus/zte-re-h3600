// module: mt7915.ko
// function: RtmpCmdQInit @ 0xc4d60
// size: 72 bytes
//

void RtmpCmdQInit(int param_1)

{
  *(undefined4 *)((int)&DAT_00285c64 + param_1) = 0;
  _raw_spin_lock_bh((int)&DAT_00285c64 + param_1);
  *(undefined4 *)(param_1 + 0x285c58) = 0;
  *(undefined4 *)(param_1 + 0x285c5c) = 0;
  *(undefined4 *)(param_1 + 0x285c54) = 0;
  *(undefined4 *)(param_1 + 0x285c60) = 1;
  _raw_spin_unlock_bh((int)&DAT_00285c64 + param_1);
  return;
}

