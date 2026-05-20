// module: tm.ko
// function: tm_ipv6table_add_set @ 0x4b9dc
// size: 256 bytes
//

undefined4 tm_ipv6table_add_set(char *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint local_5c;
  uint local_58;
  uint local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  uint local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  if (param_1 == (char *)0x0) {
    printk("ERROR:(%s:%d)","tm_api.c",0x41db);
    printk("param pp_entry is NULL\n");
    uVar2 = 0xffffffff;
  }
  else {
    uVar3 = *(uint *)(param_1 + 0x18);
    local_4c = *(undefined4 *)(param_1 + 8);
    local_48 = *(undefined4 *)(param_1 + 0xc);
    local_3c = (uVar3 << 0x1a) >> 0x1f | (uVar3 & 0x1f) << 1 | uVar3 & 0xc0;
    local_44 = *(undefined4 *)(param_1 + 0x10);
    local_58 = (uint)(param_1[1] != '\0');
    local_40 = *(undefined4 *)(param_1 + 0x14);
    local_38 = *(undefined4 *)(param_1 + 0x1c);
    local_34 = *(undefined4 *)(param_1 + 0x20);
    local_54 = (uint)(param_1[2] != '\0');
    local_30 = *(undefined4 *)(param_1 + 0x24);
    local_2c = *(undefined4 *)(param_1 + 0x28);
    local_50 = *(undefined4 *)(param_1 + 4);
    local_5c = (uint)(*param_1 != '\0');
    iVar1 = sbrg_add_ipv6table(&local_5c);
    uVar2 = 0;
    if (iVar1 != 0) {
      printk("tm_ipv6table_add_set fail\n");
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

