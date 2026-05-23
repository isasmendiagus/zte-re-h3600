// module: mt7915.ko
// function: HcGetChannelByBf @ 0xa9010
// size: 92 bytes
//

undefined1 HcGetChannelByBf(int param_1)

{
  int iVar1;
  
  iVar1 = RcGetBandIdxByBf(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 != 0) {
    return *(undefined1 *)(*(int *)(iVar1 + 4) + 4);
  }
  if (DebugLevel < 0) {
    return 0;
  }
  printk("%s(): no hdev can support beamform!\n","HcGetChannelByBf");
  return 0;
}

