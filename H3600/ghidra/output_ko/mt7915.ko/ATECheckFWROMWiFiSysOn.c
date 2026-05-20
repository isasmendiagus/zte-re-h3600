// module: mt7915.ko
// function: ATECheckFWROMWiFiSysOn @ 0x28cb50
// size: 268 bytes
//

bool ATECheckFWROMWiFiSysOn(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0x1f5;
  do {
    iVar1 = AsicGetFwSyncValue(param_1);
    if (iVar1 == 0) goto LAB_0028cb8c;
    os_msec_delay(1);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  if (-1 < DebugLevel) {
    printk("%s: 2. SW_SYN0 is not at init. state (SW_SYN0 = %d)\n","ATECheckFWROMWiFiSysOn",iVar1);
LAB_0028cb8c:
    if (2 < DebugLevel) {
      printk("%s: 2. power on WiFi SYS\n","ATECheckFWROMWiFiSysOn");
    }
  }
  iVar1 = 0x1f5;
  iVar3 = MtCmdPowerOnWiFiSys(param_1);
  do {
    iVar2 = AsicGetFwSyncValue(param_1);
    if (iVar2 == 1) {
      return iVar3 != 0;
    }
    os_msec_delay();
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  if (-1 < DebugLevel) {
    printk("%s: SW_SYN0 is not at init. state (SW_SYN0 = %d)\n","ATECheckFWROMWiFiSysOn",iVar2);
    return true;
  }
  return true;
}

