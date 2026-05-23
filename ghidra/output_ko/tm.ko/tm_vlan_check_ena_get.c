// module: tm.ko
// function: tm_vlan_check_ena_get @ 0x4f514
// size: 296 bytes
//

undefined4 tm_vlan_check_ena_get(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  int local_20;
  int local_1c;
  int local_18;
  undefined4 uStack_14;
  
  local_18 = 1;
  uStack_14 = 1;
  local_20 = 0;
  local_1c = 0;
  iVar1 = getPort(param_1,&local_18);
  if ((iVar1 == 0) && (local_18 != 8)) {
    if (param_3 == 0) {
      printk("ERROR:(%s:%d)","tm_api.c",0x51d);
      printk("param pp_ena is NULL\n");
    }
    else {
      if (param_2 == 0) {
        iVar1 = sbrg_get_inport_vl_chk_en(local_18,&local_20);
        if (iVar1 == 0) {
          *(bool *)param_3 = local_20 != 0;
          return 0;
        }
      }
      else {
        if (param_2 != 1) {
          printk("param p_mode %d is invalid\n",param_2);
          return 0xffffffff;
        }
        iVar1 = sbrg_get_outport_vl_chk_en(local_18,&local_1c);
        if (iVar1 == 0) {
          *(bool *)param_3 = local_1c != 0;
          return 0;
        }
      }
      printk("tm_vlan_check_ena_get fail\n");
    }
  }
  else {
    printk("tm_vlan_check_ena_get fail, error port %d\n",param_1);
  }
  return 0xffffffff;
}

