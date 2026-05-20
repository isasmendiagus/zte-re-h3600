// module: mt7915.ko
// function: RTMPIoctlSetWSCOOB @ 0x3edb8
// size: 348 bytes
//

void RTMPIoctlSetWSCOOB(int *param_1)

{
  char *pcVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = *param_1;
  uVar3 = (uint)*(byte *)(iVar2 + 0x3c);
  *(int **)(iVar2 + 0x40) = param_1 + uVar3 * 0x160d + 0xadc9d;
  if (*(int *)(iVar2 + 0x38) == 0x400) {
    if (2 < DebugLevel) {
      pcVar1 = "IF(apcli%d) Set_WscPinCode_Proc:: Ap Client doesn\'t need this command.\n";
      goto LAB_0003eef8;
    }
  }
  else {
    Set_WscSetupLock_Proc(param_1,&_LC38);
    Set_AP_WscConfStatus_Proc(param_1,&_LC39);
    Set_SecAuthMode_Proc(param_1,"WPAPSK");
    Set_SecEncrypType_Proc(param_1,&_LC809);
    pcVar1 = (char *)vmalloc(0x21);
    if (pcVar1 != (char *)0x0) {
      __memzero(pcVar1,0x21);
      snprintf(pcVar1,0x21,"RalinkInitialAP%02X%02X%02X",
               (uint)*(byte *)(param_1 + uVar3 * 0x160d + 0xadc9b),
               (uint)*(byte *)((int)param_1 + uVar3 * 0x5834 + 0x2b726d),
               (uint)*(byte *)((int)param_1 + uVar3 * 0x5834 + 0x2b726e));
      Set_AP_SSID_Proc(param_1,pcVar1);
      vfree(pcVar1);
    }
    Set_SecWPAPSK_Proc(param_1,"RalinkInitialAPxx1234");
    if (2 < DebugLevel) {
      pcVar1 = "IF(ra%d) Set_WscOOB_Proc\n";
LAB_0003eef8:
      printk(pcVar1,uVar3);
      return;
    }
  }
  return;
}

