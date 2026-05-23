// module: mt7915.ko
// function: ba_flush_reordering_timeout_mpdus @ 0xa58c4
// size: 308 bytes
//

void ba_flush_reordering_timeout_mpdus(int param_1,undefined4 param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  ushort uVar3;
  
  if (param_3 == 0) {
    return;
  }
  if (0 < *(int *)(param_3 + 0x34)) {
    iVar2 = *(int *)(param_3 + 0x18);
    if ((iVar2 - param_4) + 0x19 < 0) {
      if (3 < DebugLevel) {
        printk("timeout[%d] (%08lx-%08lx = %d > %d): %x, flush all!\n ",*(int *)(param_3 + 0x34),
               param_4,iVar2,param_4 - iVar2,0x96,*(undefined2 *)(param_3 + 0xc));
      }
      FUN_000a4598(param_1,param_2,param_3);
      *(int *)(param_1 + 0x9dd10) = *(int *)(param_1 + 0x9dd10) + 1;
      *(int *)(param_3 + 0x18) = param_4;
      return;
    }
    if ((iVar2 - param_4) + 10 < 0) {
      uVar3 = *(short *)(param_3 + 0xc) + 1;
      FUN_000a46ac();
      *(ushort *)(param_3 + 0xc) = uVar3 & 0xfff;
      iVar1 = FUN_000a4804(param_1,param_2,param_3,uVar3 & 0xfff);
      iVar2 = DebugLevel;
      if (iVar1 != 0xffff) {
        *(int *)(param_3 + 0x18) = param_4;
        iVar2 = DebugLevel;
        *(short *)(param_3 + 0xc) = (short)iVar1;
      }
      *(int *)(param_1 + 0x9dd00) = *(int *)(param_1 + 0x9dd00) + 1;
      if (3 < iVar2) {
        printk("%x, flush one!\n",*(undefined2 *)(param_3 + 0xc));
        return;
      }
    }
  }
  return;
}

