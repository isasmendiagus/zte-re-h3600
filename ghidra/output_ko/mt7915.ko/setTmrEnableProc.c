// module: mt7915.ko
// function: setTmrEnableProc @ 0xbb0d8
// size: 192 bytes
//

undefined4 setTmrEnableProc(int param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar2 = os_str_tol(param_2,0,10);
  if (uVar2 < 3) {
    iVar3 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
    if (iVar3 == 2) {
      TmrCtrl(param_1,uVar2 & 0xff,*(undefined1 *)(iVar1 + 0x14f));
      return 1;
    }
    if (-1 < DebugLevel) {
      printk("%s: chipcap is not HIF_MT\n","setTmrEnableProc");
      return 0;
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s: enable is incorrect!!\n","setTmrEnableProc");
  }
  return 0;
}

