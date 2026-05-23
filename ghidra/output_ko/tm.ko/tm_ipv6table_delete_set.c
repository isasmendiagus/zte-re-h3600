// module: tm.ko
// function: tm_ipv6table_delete_set @ 0x4d138
// size: 156 bytes
//

undefined4 tm_ipv6table_delete_set(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_4c [8];
  uint local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  if (param_1 == 0) {
    uVar2 = tm_ipv6table_delete_set_part_18();
  }
  else {
    local_3c = *(undefined4 *)(param_1 + 8);
    local_38 = *(undefined4 *)(param_1 + 0xc);
    local_34 = *(undefined4 *)(param_1 + 0x10);
    local_30 = *(undefined4 *)(param_1 + 0x14);
    local_28 = *(undefined4 *)(param_1 + 0x1c);
    local_24 = *(undefined4 *)(param_1 + 0x20);
    local_20 = *(undefined4 *)(param_1 + 0x24);
    local_1c = *(undefined4 *)(param_1 + 0x28);
    local_40 = *(undefined4 *)(param_1 + 4);
    local_44 = (uint)(*(char *)(param_1 + 2) != '\0');
    iVar1 = sbrg_delete_ipv6table(auStack_4c);
    uVar2 = 0;
    if (iVar1 != 0) {
      printk("tm_ipv6table_delete_set fail\n");
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

