// module: mt7915.ko
// function: HwCtrlHandleUpdateBeacon @ 0xaf3d4
// size: 604 bytes
//

undefined4 HwCtrlHandleUpdateBeacon(int param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  iVar4 = **(int **)(param_2 + 8);
  uVar1 = (undefined1)(*(int **)(param_2 + 8))[1];
  if (2 < DebugLevel) {
    printk("%s(): Update reason: %d\n","HwCtrlHandleUpdateBeacon",uVar1);
  }
  switch(uVar1) {
  case 0:
  case 1:
  case 2:
  case 8:
    iVar2 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
    if (iVar2 == 2) {
      if (iVar4 == 0) {
        if (-1 < DebugLevel) {
          printk("%s(): wdev = NULL, reason(%d)\n","HwCtrlHandleUpdateBeacon",uVar1);
        }
      }
      else {
        UpdateBeaconProc(param_1,iVar4,0,0,1);
      }
    }
    break;
  case 3:
    iVar4 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
    if (iVar4 == 2) {
      piVar3 = (int *)(param_1 + 8);
      do {
        piVar3 = piVar3 + 1;
        if (*piVar3 != 0) {
          UpdateBeaconProc(param_1,*piVar3,0,0,1);
        }
      } while (piVar3 != (int *)(param_1 + 0x1a8));
    }
    break;
  case 4:
    if (*(char *)(param_1 + 0x286285) == '\x01') {
      QBSS_LoadUpdate(param_1,jiffies);
      RRM_QuietUpdata(param_1);
      updateBeaconRoutineCase(param_1,1);
    }
    break;
  case 5:
    if (((iVar4 != 0) &&
        (iVar2 = *(int *)(iVar4 + 0x14),
        (iVar2 - 0x10U & 0xffffffef) == 0 || (iVar2 == 1 || iVar2 == 4))) &&
       (*(char *)(iVar4 + 0xb1c) != '\0')) {
      if (*(char *)(iVar4 + 0x988) == '\x02') {
        *(undefined1 *)(iVar4 + 0x950) = 1;
        UpdateBeaconProc(param_1,iVar4,0,0,1);
      }
      else {
        AsicEnableBeacon(param_1,iVar4);
      }
    }
    break;
  case 6:
    if ((iVar4 != 0) &&
       (iVar2 = *(int *)(iVar4 + 0x14),
       (iVar2 - 0x10U & 0xffffffef) == 0 || (iVar2 == 1 || iVar2 == 4))) {
      if (*(char *)(iVar4 + 0x988) == '\x02') {
        *(undefined1 *)(iVar4 + 0x950) = 0;
        UpdateBeaconProc(param_1,iVar4,0,0,0);
      }
      else {
        AsicDisableBeacon(param_1,iVar4);
      }
    }
    break;
  default:
    if (-1 < DebugLevel) {
      printk("%s(): Wrong Update reason: %d\n","HwCtrlHandleUpdateBeacon",uVar1);
    }
  }
  return 0;
}

