// module: tm.ko
// function: tm_ipv4table_lookup_get @ 0x4cefc
// size: 220 bytes
//

undefined4 tm_ipv4table_lookup_get(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int local_2c;
  int local_28;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  if (param_1 == 0) {
    printk("ERROR:(%s:%d)","tm_api.c",0x40ff);
    printk("param pp_entry is NULL\n");
    uVar2 = 0xffffffff;
  }
  else {
    local_1c = *(undefined4 *)(param_1 + 8);
    local_20 = *(undefined4 *)(param_1 + 4);
    local_18 = *(undefined4 *)(param_1 + 0xc);
    iVar1 = sbrg_lookup_ipv4table(&local_2c);
    if (iVar1 == 0) {
      *(bool *)(param_1 + 1) = local_28 != 0;
      *(bool *)(param_1 + 2) = local_24 != 0;
      *(bool *)param_1 = local_2c != 0;
      uVar2 = sbrg_change_portmask(local_14);
      *(undefined4 *)(param_1 + 0x10) = uVar2;
      uVar2 = 0;
    }
    else {
      printk("ERROR:(%s:%d)","tm_api.c",0x410a);
      printk("tm_ipv4table_lookup_get fail\n");
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

