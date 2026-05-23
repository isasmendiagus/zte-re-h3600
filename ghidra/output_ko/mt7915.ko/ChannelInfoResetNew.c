// module: mt7915.ko
// function: ChannelInfoResetNew @ 0x24418
// size: 96 bytes
//

void ChannelInfoResetNew(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int *piVar1;
  undefined4 extraout_r2;
  
  piVar1 = (int *)HcGetAutoChCtrlbyBandIdx();
  if (*piVar1 != 0) {
    __memzero(*piVar1,0x514);
    (&DAT_0036b861)[param_1] = 0;
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("pChannelInfo equal NULL, band:%d\n",param_2,extraout_r2,param_4);
  return;
}

