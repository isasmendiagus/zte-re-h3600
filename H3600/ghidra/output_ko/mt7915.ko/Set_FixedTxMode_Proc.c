// module: mt7915.ko
// function: Set_FixedTxMode_Proc @ 0xdff40
// size: 176 bytes
//

undefined4
Set_FixedTxMode_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = *param_1;
  uVar1 = RT_CfgSetFixedTxPhyMode(param_2);
  if (*(char *)((int)param_1 + 0x286285) == '\x01') {
    iVar2 = *(int *)(iVar2 + 0x3c) * 0x160d + 0xadc92;
  }
  else {
    if (*(char *)((int)param_1 + 0x286285) != '\0') goto LAB_000dffa4;
    iVar2 = *(int *)(iVar2 + 0x3c) * 0x84dec + 0xdb6d6;
  }
  param_1 = param_1 + iVar2;
  if (param_1 != (int *)0x0) {
    *(byte *)((int)param_1 + 0x8af) =
         *(byte *)((int)param_1 + 0x8af) & 199 | (byte)((uVar1 & 7) << 3);
  }
LAB_000dffa4:
  if (2 < DebugLevel) {
    printk("%s():(FixedTxMode=%d)\n","Set_FixedTxMode_Proc",uVar1,DebugLevel,param_4);
  }
  return 1;
}

