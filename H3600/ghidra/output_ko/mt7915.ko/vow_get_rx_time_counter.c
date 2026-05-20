// module: mt7915.ko
// function: vow_get_rx_time_counter @ 0x41d90
// size: 452 bytes
//

undefined4 vow_get_rx_time_counter(undefined4 param_1,int param_2,undefined4 param_3)

{
  undefined1 uVar1;
  undefined4 uVar2;
  undefined2 local_5c;
  undefined2 local_5a;
  undefined4 local_44;
  undefined1 local_40;
  undefined4 local_3c;
  undefined1 local_38;
  undefined4 local_34;
  
  __memzero(&local_5c,0x44);
  local_5a = (undefined2)param_2;
  local_5c = 4;
  uVar1 = (undefined1)param_3;
  if (param_2 == 2) {
    local_38 = uVar1;
    if (2 < DebugLevel) {
      printk("%s:(cmd = 0x%x, subcmd = 0x%x, target = 0x%x, band_idx = 0x%x)\n",
             "vow_get_rx_time_counter",4,2,2,param_3);
    }
    uVar2 = MtCmdGetVoWRxAirtimeCtrl(param_1,&local_5c);
    if (DebugLevel < 3) {
      return local_3c;
    }
  }
  else if (param_2 == 3) {
    if (2 < DebugLevel) {
      printk("%s:(Not implemented yet = 0x%x)\n","vow_get_rx_time_counter",3);
    }
    uVar2 = MtCmdGetVoWRxAirtimeCtrl(param_1,&local_5c);
    if (DebugLevel < 3) {
      return local_34;
    }
  }
  else if (param_2 == 1) {
    local_40 = uVar1;
    if (2 < DebugLevel) {
      printk("%s:(cmd = 0x%x, subcmd = 0x%x, target = 0x%x, band_idx = 0x%x)\n",
             "vow_get_rx_time_counter",4,1,1,param_3);
    }
    uVar2 = MtCmdGetVoWRxAirtimeCtrl(param_1,&local_5c);
    if (DebugLevel < 3) {
      return local_44;
    }
  }
  else {
    if (2 < DebugLevel) {
      printk("%s:(No such command = 0x%x)\n","vow_get_rx_time_counter",param_2);
    }
    uVar2 = MtCmdGetVoWRxAirtimeCtrl(param_1,&local_5c);
    if (DebugLevel < 3) goto LAB_00041e04;
  }
  printk("%s:(ret = %d), sizeof %zu\n","vow_get_rx_time_counter",uVar2,0x44);
LAB_00041e04:
  if (param_2 == 1) {
    return local_44;
  }
  if (param_2 == 2) {
    return local_3c;
  }
  if (param_2 != 3) {
    local_34 = 0xffffffff;
  }
  return local_34;
}

