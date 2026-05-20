// module: tm.ko
// function: tm_ipv6table_lookup_get @ 0x4b8d0
// size: 268 bytes
//

undefined4 tm_ipv6table_lookup_get(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int local_4c;
  int local_48;
  int local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  if (param_1 == 0) {
    printk("ERROR:(%s:%d)","tm_api.c",0x41a6);
    printk("param pp_entry is NULL\n");
    uVar2 = 0xffffffff;
  }
  else {
    local_30 = *(undefined4 *)(param_1 + 0x14);
    local_3c = *(undefined4 *)(param_1 + 8);
    local_38 = *(undefined4 *)(param_1 + 0xc);
    local_34 = *(undefined4 *)(param_1 + 0x10);
    local_28 = *(undefined4 *)(param_1 + 0x1c);
    local_24 = *(undefined4 *)(param_1 + 0x20);
    local_20 = *(undefined4 *)(param_1 + 0x24);
    local_1c = *(undefined4 *)(param_1 + 0x28);
    local_40 = *(undefined4 *)(param_1 + 4);
    iVar1 = sbrg_lookup_ipv6table(&local_4c);
    if (iVar1 == 0) {
      *(bool *)(param_1 + 1) = local_48 != 0;
      *(bool *)(param_1 + 2) = local_44 != 0;
      *(bool *)param_1 = local_4c != 0;
      uVar2 = sbrg_change_portmask(local_2c);
      *(undefined4 *)(param_1 + 0x18) = uVar2;
      uVar2 = 0;
    }
    else {
      printk("ERROR:(%s:%d)","tm_api.c",0x41b7);
      printk("tm_ipv6table_lookup_get fail\n");
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

