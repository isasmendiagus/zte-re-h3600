// module: tm.ko
// function: tm_mac_ramaddr_sel_set @ 0x4c7e8
// size: 308 bytes
//

undefined4 tm_mac_ramaddr_sel_set(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_18;
  int local_14 [2];
  
  switch(param_1) {
  case 0:
    iVar2 = tm_mac_aging_cycle_get(local_14);
    if (iVar2 != 0) goto LAB_0004c918;
    iVar2 = local_14[0] * 0x710;
    iVar3 = 0;
    break;
  case 1:
    iVar2 = tm_mac_aging_cycle_get(local_14);
    if (iVar2 != 0) goto LAB_0004c918;
    iVar3 = 1;
    iVar2 = local_14[0] * 0x1c40;
    break;
  case 2:
    iVar2 = tm_mac_aging_cycle_get(local_14);
    if (iVar2 != 0) goto LAB_0004c918;
    iVar3 = 2;
    iVar2 = local_14[0] * 0xe20;
    break;
  case 3:
    iVar2 = tm_mac_aging_cycle_get(local_14);
    if (iVar2 == 0) {
      printk("Sel3 is not support\n");
      return 0xffffffff;
    }
    goto LAB_0004c918;
  default:
    printk("tm_mac_ramaddr_sel_set fail, error p_sel %d\n",param_1);
    return 0xffffffff;
  }
  iVar1 = sbrg_get_table_sel(&local_18);
  if (((iVar1 == 0) &&
      (((local_18 == iVar3 || (iVar1 = tm_port_clear_macaddr_set(0xff), iVar1 == 0)) &&
       (iVar3 = sbrg_set_table_sel(iVar3), iVar3 == 0)))) &&
     (iVar2 = sbrg_set_srcaddr_aging_cycle(iVar2), iVar2 == 0)) {
    return 0;
  }
LAB_0004c918:
  printk("tm_mac_ramaddr_sel_set fail\n");
  return 0xffffffff;
}

