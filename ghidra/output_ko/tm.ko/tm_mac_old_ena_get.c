// module: tm.ko
// function: tm_mac_old_ena_get @ 0x4ca08
// size: 128 bytes
//

undefined4 tm_mac_old_ena_get(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int local_c;
  
  local_c = 0;
  if (param_1 == 0) {
    printk("ERROR:(%s:%d)","tm_api.c",0x2c9d);
    printk("param pp_ena is NULL\n");
    uVar2 = 0xffffffff;
  }
  else {
    iVar1 = sbrg_get_macaddr_age_en(&local_c);
    if (iVar1 == 0) {
      *(bool *)param_1 = local_c != 0;
      uVar2 = 0;
    }
    else {
      printk("tm_mac_old_ena_get fail\n");
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

