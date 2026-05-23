// module: mt7915.ko
// function: txbf_bfee_adaption @ 0x88d44
// size: 180 bytes
//

undefined1 txbf_bfee_adaption(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  
  iVar2 = has_rtk_sta_bfer();
  if (iVar2 == 0) {
    if (*(char *)(param_1 + 0xa789d4) == '\0') {
      uVar1 = AsicTxBfeeHwCtrl(param_1,1);
      iVar2 = DebugLevel;
      *(undefined1 *)(param_1 + 0xa789d4) = 1;
      if (iVar2 < 3) {
        return uVar1;
      }
      printk("Enable BFee\n");
      return uVar1;
    }
  }
  else if (*(char *)(param_1 + 0xa789d4) != '\0') {
    uVar1 = AsicTxBfeeHwCtrl(param_1,0);
    iVar2 = DebugLevel;
    *(undefined1 *)(param_1 + 0xa789d4) = 0;
    if (iVar2 < 3) {
      return uVar1;
    }
    printk("Disable BFee\n");
    return uVar1;
  }
  return 1;
}

