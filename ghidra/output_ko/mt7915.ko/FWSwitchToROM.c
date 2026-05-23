// module: mt7915.ko
// function: FWSwitchToROM @ 0x28cc60
// size: 112 bytes
//

int FWSwitchToROM(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 extraout_r2;
  
  if (2 < DebugLevel) {
    printk(&_LC3,"FWSwitchToROM",param_3,DebugLevel,param_4);
  }
  NICRestartFirmware(param_1);
  iVar1 = ATECheckFWROMWiFiSysOn(param_1);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s, CheckFWROMWiFiSysOn  failed\n","FWSwitchToROM",extraout_r2,DebugLevel,param_4);
  }
  return iVar1;
}

