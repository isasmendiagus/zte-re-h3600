// module: mt7915.ko
// function: Set_TpcCtrl_Proc @ 0x140374
// size: 440 bytes
//

undefined4 Set_TpcCtrl_Proc(undefined4 param_1,char *param_2)

{
  size_t sVar1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  uint uVar5;
  int iVar6;
  uint local_24 [3];
  
  sVar1 = strlen(param_2);
  uVar5 = 0;
  local_24[0] = 0;
  if (sVar1 != 0) {
    pcVar4 = param_2 + -1;
    iVar6 = 1;
    do {
      pcVar4 = pcVar4 + 1;
      uVar5 = uVar5 + 1;
      if (*pcVar4 == ':') {
        *pcVar4 = '\0';
        local_24[iVar6] = uVar5;
        iVar6 = iVar6 + 1;
      }
    } while (uVar5 < sVar1);
    if (iVar6 == 3) {
      uVar5 = os_str_tol(param_2,0,10);
      uVar2 = os_str_tol(param_2 + local_24[1],0,10);
      uVar3 = os_str_tol(param_2 + local_24[2],0,10);
      if (0x3e < uVar2) {
        uVar2 = 0x3f;
      }
      if (-1 < DebugLevel) {
        printk("BandIdx=%d, Power=%d, CentCh=%d\n",uVar5,uVar2,uVar3);
      }
      TxPowerTpcFeatureForceCtrl(param_1,(int)(char)uVar2,uVar5 & 0xff,uVar3 & 0xff);
      return 1;
    }
  }
  if (0 < DebugLevel) {
    printk("usage format is [band:power:channel], power unit is 0.5 dBm\n\n");
  }
  if ((((-1 < DebugLevel) && (printk("e.g.\n\n"), -1 < DebugLevel)) &&
      (printk("iwpriv ra0 set TpcCtrl=0:62:6\n"), -1 < DebugLevel)) &&
     ((printk("means (band 0), (31 dBm), (channel 6)\n\n"), -1 < DebugLevel &&
      (printk("iwpriv ra0 set TpcCtrl=1:10:100\n"), -1 < DebugLevel)))) {
    printk("means (band 1), (5 dBm), (channel 100)\n\n");
  }
  return 1;
}

