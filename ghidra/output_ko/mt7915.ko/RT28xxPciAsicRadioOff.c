// module: mt7915.ko
// function: RT28xxPciAsicRadioOff @ 0x1c90f8
// size: 92 bytes
//

undefined4
RT28xxPciAsicRadioOff(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 extraout_r2;
  
  iVar1 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 != 2) {
    return 1;
  }
  if (DebugLevel < 1) {
    return 0;
  }
  printk("%s(): Not support for HIF_MT yet!\n","RT28xxPciAsicRadioOff",extraout_r2,DebugLevel,
         param_4);
  return 0;
}

