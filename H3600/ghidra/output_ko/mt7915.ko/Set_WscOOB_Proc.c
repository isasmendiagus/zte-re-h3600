// module: mt7915.ko
// function: Set_WscOOB_Proc @ 0x3bbe0
// size: 344 bytes
//

undefined4 Set_WscOOB_Proc(int *param_1)

{
  char *__s;
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = *(uint *)(*param_1 + 0x3c);
  if (*(int *)(*param_1 + 0x38) == 0x400) {
    if (DebugLevel < 3) {
      uVar1 = 0;
    }
    else {
      printk("IF(apcli%d) Set_WscPinCode_Proc:: Ap Client doesn\'t need this command.\n",
             uVar3 & 0xff);
      uVar1 = 0;
    }
  }
  else {
    Set_WscSetupLock_Proc(param_1,&_LC38);
    Set_AP_WscConfStatus_Proc(param_1,&_LC39);
    Set_SecAuthMode_Proc(param_1,"WPA2PSK");
    Set_SecEncrypType_Proc(param_1,&_LC731);
    __s = (char *)vmalloc(0x21);
    if (__s != (char *)0x0) {
      __memzero(__s,0x21);
      uVar2 = uVar3 & 0xff;
      snprintf(__s,0x21,"RalinkInitialAP%02X%02X%02X",
               (uint)*(byte *)(param_1 + uVar2 * 0x160d + 0xadc9b),
               (uint)*(byte *)((int)param_1 + uVar2 * 0x5834 + 0x2b726d),
               (uint)*(byte *)((int)param_1 + uVar2 * 0x5834 + 0x2b726e));
      Set_AP_SSID_Proc(param_1,__s);
      vfree(__s);
    }
    Set_SecWPAPSK_Proc(param_1,"RalinkInitialAPxx1234");
    if (DebugLevel < 3) {
      uVar1 = 1;
    }
    else {
      printk("IF(ra%d) Set_WscOOB_Proc\n",uVar3 & 0xff);
      uVar1 = 1;
    }
  }
  return uVar1;
}

