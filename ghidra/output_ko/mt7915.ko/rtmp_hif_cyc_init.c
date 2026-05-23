// module: mt7915.ko
// function: rtmp_hif_cyc_init @ 0x13a330
// size: 92 bytes
//

undefined4 rtmp_hif_cyc_init(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 != 2) {
    return 1;
  }
  if (DebugLevel < 1) {
    return 0;
  }
  printk("%s(%d): Not support for HIF_MT yet!\n","rtmp_hif_cyc_init",0x1c9,DebugLevel,param_4);
  return 0;
}

