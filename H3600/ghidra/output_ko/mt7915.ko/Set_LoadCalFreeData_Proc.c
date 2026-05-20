// module: mt7915.ko
// function: Set_LoadCalFreeData_Proc @ 0x12867c
// size: 392 bytes
//

undefined4
Set_LoadCalFreeData_Proc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = os_str_tol(param_2,0,10,param_4,param_4);
  if (iVar1 == 1) {
    iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
    if ((*(code **)(iVar1 + 0x8c) == (code *)0x0) ||
       (iVar1 = (**(code **)(iVar1 + 0x8c))(param_1), iVar1 == 0)) {
      if (0 < DebugLevel) {
        printk("Merge fail\n");
        return 1;
      }
    }
    else {
      iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
      if (*(code **)(iVar1 + 0x90) != (code *)0x0) {
        (**(code **)(iVar1 + 0x90))(param_1);
        "cp_support_is_enabled"[param_1 + 6] = "cp_support_is_enabled"[param_1 + 6] | 1;
      }
      if (0 < DebugLevel) {
        printk("Merge successfully");
        if ("cp_support_is_enabled"[param_1 + 5] == '\x02') {
          if (DebugLevel < 1) {
            return 1;
          }
          printk(",plz write back to flash");
        }
        if (0 < DebugLevel) {
          printk(&_LC71);
        }
      }
    }
  }
  else {
    if (iVar1 != 2) {
      return 0;
    }
    iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
    if (*(code **)(iVar1 + 0x90) != (code *)0x0) {
      (**(code **)(iVar1 + 0x90))(param_1);
      "cp_support_is_enabled"[param_1 + 6] = "cp_support_is_enabled"[param_1 + 6] | 1;
    }
    if (0 < DebugLevel) {
      printk("Merge successfully");
      return 1;
    }
  }
  return 1;
}

