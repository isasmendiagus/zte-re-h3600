// module: mt7915.ko
// function: ZTE_Show_Hop_Num @ 0x161a88
// size: 92 bytes
//

undefined4 ZTE_Show_Hop_Num(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if ((*(int *)(*param_1 + 0x38) - 0x100U & 0xfffffeff) != 0) {
    return 0;
  }
  if (DebugLevel < 0) {
    return 1;
  }
  printk("pAd->MaxHopNum = %d\n",param_1[0x29f300],param_3,param_1 + 0x29f000,param_4);
  return 1;
}

