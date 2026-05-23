// module: mt7915.ko
// function: ZTE_Set_Hop_Num_Proc @ 0x161a00
// size: 136 bytes
//

undefined4 ZTE_Set_Hop_Num_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = simple_strtol(param_2,0,10);
  iVar1 = DebugLevel;
  if (7 < (uVar2 & 0xff) || (*(int *)(*param_1 + 0x38) - 0x100U & 0xfffffeff) != 0) {
    return 0;
  }
  param_1[0x29f300] = uVar2 & 0xff;
  if (-1 < iVar1) {
    printk("pAd->MaxHopNum = %d\n");
    return 1;
  }
  return 1;
}

