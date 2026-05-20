// module: mt7915.ko
// function: StaRecBfeeUpdate @ 0x88464
// size: 112 bytes
//

void StaRecBfeeUpdate(int param_1,undefined2 *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  *param_2 = 0x14;
  param_2[1] = 8;
  iVar1 = DebugLevel;
  *(undefined1 *)(param_2 + 2) = *(undefined1 *)(param_1 + 0xc64);
  *(undefined1 *)((int)param_2 + 5) = *(undefined1 *)(param_1 + 0xc65);
  if (iVar1 < 3) {
    return;
  }
  printk("%s() fgFbIdentityMatrix: %u\n","StaRecBfeeUpdate");
  if (DebugLevel < 3) {
    return;
  }
  printk("%s() fgIgnFbk: %u\n","StaRecBfeeUpdate",*(undefined1 *)((int)param_2 + 5),param_4);
  return;
}

