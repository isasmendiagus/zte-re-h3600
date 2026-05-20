// module: tm.ko
// function: tm_ipv4table_delete_set @ 0x4d0a8
// size: 144 bytes
//

undefined4 tm_ipv4table_delete_set(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_24 [8];
  uint local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  if (param_1 == 0) {
    printk("ERROR:(%s:%d)","tm_api.c",0x415c);
    printk("param pp_entry is NULL\n");
    uVar2 = 0xffffffff;
  }
  else {
    local_14 = *(undefined4 *)(param_1 + 8);
    local_18 = *(undefined4 *)(param_1 + 4);
    local_10 = *(undefined4 *)(param_1 + 0xc);
    local_1c = (uint)(*(char *)(param_1 + 2) != '\0');
    iVar1 = sbrg_delete_ipv4table(auStack_24);
    uVar2 = 0;
    if (iVar1 != 0) {
      printk("tm_ipv4table_delete_set fail\n");
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

