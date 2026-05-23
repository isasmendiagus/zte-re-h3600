// module: tm.ko
// function: tm_ipv4table_add_set @ 0x4cfd8
// size: 208 bytes
//

undefined4 tm_ipv4table_add_set(char *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint local_34;
  uint local_30;
  uint local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  uint local_1c;
  
  if (param_1 == (char *)0x0) {
    printk("ERROR:(%s:%d)","tm_api.c",0x412e);
    printk("param pp_entry is NULL\n");
    uVar2 = 0xffffffff;
  }
  else {
    uVar3 = *(uint *)(param_1 + 0x10);
    local_24 = *(undefined4 *)(param_1 + 8);
    local_28 = *(undefined4 *)(param_1 + 4);
    local_1c = (uVar3 << 0x1a) >> 0x1f | (uVar3 & 0x1f) << 1 | uVar3 & 0xc0;
    local_20 = *(undefined4 *)(param_1 + 0xc);
    local_30 = (uint)(param_1[1] != '\0');
    local_2c = (uint)(param_1[2] != '\0');
    local_34 = (uint)(*param_1 != '\0');
    iVar1 = sbrg_add_ipv4table(&local_34);
    uVar2 = 0;
    if (iVar1 != 0) {
      printk("tm_ipv4table_add_set fail\n");
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

