// module: mt7915.ko
// function: set_background_scan_cfg @ 0xea570
// size: 172 bytes
//

undefined4 set_background_scan_cfg(int param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = sscanf(param_2,"%d");
  iVar1 = DebugLevel;
  if (iVar2 == 1) {
    *(undefined1 *)(param_1 + 0xa7979d) = 0;
    if (2 < iVar1) {
      printk("ipith = %d\n");
    }
  }
  else if (-1 < DebugLevel) {
    printk("Format Error!\n");
    if (-1 < DebugLevel) {
      printk("iwpriv ra0 set bgndscancfg=[IPI_TH]\n");
    }
  }
  return 1;
}

