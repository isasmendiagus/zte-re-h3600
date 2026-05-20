// module: tm.ko
// function: tm_port_multicast_act_set @ 0x4fcf8
// size: 160 bytes
//

undefined4 tm_port_multicast_act_set(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_18 [3];
  
  iVar1 = getPort(param_1,local_18);
  if ((iVar1 == 0) && (local_18[0] != 8)) {
    iVar1 = param_2;
    if (((param_2 != 1) && (iVar1 = 0, param_2 != 0)) && (iVar1 = param_2, param_2 != 2)) {
      printk("tm_port_multicast_act_set fail, error param %d\n",param_2);
      return 0xffffffff;
    }
    iVar1 = sbrg_set_multicst_transmit_ctrl(local_18[0],iVar1);
    uVar2 = 0;
    if (iVar1 != 0) {
      printk("tm_port_multicast_act_set fail\n");
      uVar2 = 0xffffffff;
    }
  }
  else {
    printk("tm_port_multicast_act_set fail, error port %d\n",param_1);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

