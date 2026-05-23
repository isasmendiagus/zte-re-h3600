// module: mt7915.ko
// function: rc_radio_exit @ 0xac268
// size: 96 bytes
//

void rc_radio_exit(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 0;
  uVar2 = (uint)(*(int *)(param_1 + 0xb58) << 0x1a) >> 0x1f;
  if (param_2 == 0) {
    uVar2 = 0;
  }
  if (uVar2 == 0) {
    *(undefined1 *)(param_1 + 0x32d8) = 1;
  }
  else {
    *(undefined1 *)(param_1 + 0x32d8) = 2;
  }
  do {
    iVar1 = uVar3 * 0x354;
    uVar3 = uVar3 + 1 & 0xff;
    os_free_mem(*(undefined4 *)(iVar1 + param_1 + 0x16b0));
  } while (uVar3 < *(byte *)(param_1 + 0x32d8));
  return;
}

