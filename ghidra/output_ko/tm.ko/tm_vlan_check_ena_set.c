// module: tm.ko
// function: tm_vlan_check_ena_set @ 0x4f1e4
// size: 180 bytes
//

undefined4 tm_vlan_check_ena_set(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int local_18 [2];
  
  iVar1 = getPort(param_1,local_18);
  if ((iVar1 == 0) && (local_18[0] != 8)) {
    if (param_2 == 0) {
      iVar1 = sbrg_set_inport_vl_chk_en(local_18[0],param_3 != 0);
    }
    else {
      if (param_2 != 1) {
        printk("param p_mode %d is invalid\n",param_2);
        return 0xffffffff;
      }
      iVar1 = sbrg_set_outport_vl_chk_en(local_18[0],param_3 != 0);
    }
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      printk("tm_vlan_check_ena_set fail\n");
      uVar2 = 0xffffffff;
    }
  }
  else {
    printk("tm_vlan_check_ena_set fail, error port %d\n",param_1);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

