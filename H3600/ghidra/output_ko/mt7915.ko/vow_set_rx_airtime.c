// module: mt7915.ko
// function: vow_set_rx_airtime @ 0x416f8
// size: 480 bytes
//

undefined4 vow_set_rx_airtime(int param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  undefined2 local_54;
  undefined2 local_52;
  undefined1 local_3c;
  
  __memzero(&local_54,0x44);
  local_54 = (undefined2)param_2;
  local_52 = (undefined2)param_3;
  switch(param_2) {
  case 1:
    if (param_3 == 1) {
      local_3c = *(undefined1 *)(param_1 + 0xa79826);
      if (2 < DebugLevel) {
        printk("%s:(cmd = 0x%x, subcmd = 0x%x, value = 0x%x)\n","vow_set_rx_airtime",1,1,local_3c);
      }
      goto LAB_0004175c;
    }
    goto LAB_0004178c;
  case 2:
    if (param_3 == 1) {
      local_3c = 1;
      if (2 < DebugLevel) {
        printk("%s:(cmd = 0x%x, subcmd = 0x%x, value = 0x%x)\n","vow_set_rx_airtime",2,1,1);
      }
      goto LAB_0004175c;
    }
LAB_0004178c:
    if (param_3 == 2) {
      if (2 < DebugLevel) {
        printk("%s:(Not implemented yet = 0x%x)\n","vow_set_rx_airtime",2);
      }
      goto LAB_0004175c;
    }
    break;
  case 3:
    if (param_3 == 1) {
      local_3c = *(undefined1 *)(param_1 + 0xa797dc);
      if (2 < DebugLevel) {
        printk("%s:(cmd = 0x%x, subcmd =  0x%x, value = 0x%x)\n","vow_set_rx_airtime",3,1,local_3c);
      }
      goto LAB_0004175c;
    }
    break;
  case 4:
    break;
  default:
    if (2 < DebugLevel) {
      printk("%s:(No such command = 0x%x)\n","vow_set_rx_airtime",param_3);
    }
    goto LAB_0004175c;
  }
  if (2 < DebugLevel) {
    printk("%s:(No such sub command = 0x%x)\n","vow_set_rx_airtime",param_3);
  }
LAB_0004175c:
  uVar1 = MtCmdSetVoWRxAirtimeCtrl(param_1,&local_54);
  if (2 < DebugLevel) {
    printk("%s:(ret = %d), sizeof %zu\n","vow_set_rx_airtime",uVar1,0x44);
  }
  return uVar1;
}

