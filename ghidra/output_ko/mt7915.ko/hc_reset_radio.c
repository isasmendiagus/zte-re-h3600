// module: mt7915.ko
// function: hc_reset_radio @ 0xaa2b8
// size: 152 bytes
//

undefined4 hc_reset_radio(int param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined1 auStack_2b [3];
  undefined1 local_28;
  undefined1 local_26;
  undefined1 local_25;
  undefined1 local_24;
  
  iVar3 = *(int *)(param_1 + 0xa797a0);
  if (*(char *)(iVar3 + 0x32d8) != '\0') {
    uVar1 = 0;
    do {
      os_zero_mem(auStack_2b,0xb);
      iVar4 = *(int *)(iVar3 + uVar1 * 0x1c + 4);
      uVar2 = uVar1 + 1 & 0xff;
      local_26 = *(undefined1 *)(iVar4 + 4);
      local_25 = *(undefined1 *)(iVar4 + 6);
      local_28 = *(undefined1 *)(iVar4 + 7);
      local_24 = *(undefined1 *)(iVar4 + 5);
      AsicSwitchChannel(param_1,uVar1,auStack_2b,0);
      uVar1 = uVar2;
    } while (uVar2 < *(byte *)(iVar3 + 0x32d8));
  }
  return 1;
}

