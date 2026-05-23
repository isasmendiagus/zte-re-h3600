// module: mt7915.ko
// function: Set_themal_sensor @ 0xbe0c8
// size: 308 bytes
//

undefined4 Set_themal_sensor(int *param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 local_1c [2];
  
  local_1c[0] = 0;
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  uVar2 = os_str_tol(param_2,0,10);
  if (uVar2 < 2) {
    if (iVar1 == 0) {
      if (DebugLevel < 1) {
        return 0;
      }
      printk("%s: wdev is invalid\n","Set_themal_sensor");
      return 0;
    }
    uVar3 = HcGetBandByWdev(iVar1);
    MtCmdGetThermalSensorResult(param_1,uVar2 & 0xff,uVar3,local_1c);
    if (uVar2 == 1) {
      if (0 < DebugLevel) {
        printk("%s: ADC Value = %d [0x%x]\n","Set_themal_sensor",local_1c[0],local_1c[0]);
        return 1;
      }
    }
    else if (0 < DebugLevel) {
      printk("%s: TMP Value = %d [0x%x]\n","Set_themal_sensor",local_1c[0],local_1c[0]);
    }
  }
  else if (0 < DebugLevel) {
    printk("%s: 0: get temperature; 1: get adc\n","Set_themal_sensor");
    return 1;
  }
  return 1;
}

