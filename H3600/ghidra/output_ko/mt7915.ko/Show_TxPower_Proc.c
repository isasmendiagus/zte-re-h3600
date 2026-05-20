// module: mt7915.ko
// function: Show_TxPower_Proc @ 0xd5a3c
// size: 200 bytes
//

undefined4 Show_TxPower_Proc(int *param_1,char *param_2,size_t param_3,undefined4 param_4)

{
  uint uVar1;
  
  if ((uint)*(byte *)((int)param_1 + 0x2b7242) <= (uint)*(byte *)(*param_1 + 0x3c)) {
    return 0;
  }
  HcGetBandByWdev(param_1 + (uint)*(byte *)(*param_1 + 0x3c) * 0x160d + 0xadc92);
  uVar1 = HcGetBandByWdev(param_1 + 0xdb6d6);
  if (0 < DebugLevel) {
    printk("%s: BandIdx = %d\n","Show_TxPower_Proc",uVar1,DebugLevel,param_4);
  }
  if (1 < uVar1) {
    return 1;
  }
  snprintf(param_2,param_3,"\t%u",(uint)*(byte *)((int)param_1 + uVar1 + 0x794cd8));
  return 0;
}

