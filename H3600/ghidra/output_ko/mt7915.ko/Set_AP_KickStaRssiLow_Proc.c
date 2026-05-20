// module: mt7915.ko
// function: Set_AP_KickStaRssiLow_Proc @ 0x29c18
// size: 336 bytes
//

undefined4 Set_AP_KickStaRssiLow_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  char cVar2;
  uint uVar3;
  char *pcVar4;
  
  uVar3 = *(uint *)(*param_1 + 0x3c);
  cVar2 = os_str_tol(param_2,0,10);
  if (cVar2 == '\0') {
    if (DebugLevel < 3) {
      *(undefined1 *)((int)param_1 + (uVar3 & 0xff) * 0x5834 + 0x2bbe85) = 0;
      goto LAB_00029c6c;
    }
    printk("Disable RssiLowForStaKickOut Function\n");
  }
  else if (100 < (byte)(cVar2 + 100U)) {
    if (DebugLevel < 3) {
      return 0;
    }
    printk("RssiLowForStaKickOut Value Error.\n");
    return 0;
  }
  iVar1 = DebugLevel;
  uVar3 = uVar3 & 0xff;
  *(char *)((int)param_1 + uVar3 * 0x5834 + 0x2bbe85) = cVar2;
  if (2 < iVar1) {
    printk("I/F(ra%d) RssiLowForStaKickOut=%d\n",uVar3,(int)cVar2);
  }
LAB_00029c6c:
  if (*(char *)((int)param_1 + 0x2b7242) != '\0') {
    uVar3 = 0;
    pcVar4 = (char *)((int)param_1 + 0x2bbe85);
    do {
      if (2 < DebugLevel) {
        printk("%d. ==> %d\n",uVar3,(int)*pcVar4);
      }
      uVar3 = uVar3 + 1;
      pcVar4 = pcVar4 + 0x5834;
    } while (uVar3 < *(byte *)((int)param_1 + 0x2b7242));
  }
  return 1;
}

