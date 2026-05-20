// module: tm.ko
// function: tm_mactable_add_set @ 0x4b594
// size: 236 bytes
//

undefined4 tm_mactable_add_set(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined1 auStack_40 [4];
  uint local_3c;
  uint local_38;
  undefined4 local_34;
  undefined4 local_30;
  int local_2c;
  int local_28;
  uint local_24;
  
  if (param_1 == (undefined4 *)0x0) {
    printk("ERROR:(%s:%d)","tm_api.c",0x3f8d);
    printk("param pp_entry is NULL\n");
    uVar2 = 0xffffffff;
  }
  else {
    uVar3 = (uint)*(byte *)(param_1 + 4);
    local_30 = param_1[3];
    local_34 = *param_1;
    local_24 = (uVar3 << 0x1a) >> 0x1f | (uVar3 & 0x1f) << 1 | uVar3 & 0xc0;
    local_2c = (uint)*(byte *)(param_1 + 2) * 0x10000 +
               (uint)*(byte *)((int)param_1 + 9) * 0x1000000 +
               (uint)*(byte *)((int)param_1 + 7) * 0x100 + (uint)*(byte *)((int)param_1 + 6);
    local_38 = (uint)(*(char *)(param_1 + 1) != '\0');
    local_28 = (uint)*(byte *)((int)param_1 + 10) + (uint)*(byte *)((int)param_1 + 0xb) * 0x100;
    local_3c = (uint)(*(char *)((int)param_1 + 5) != '\0');
    iVar1 = sbrg_add_mactable(auStack_40);
    uVar2 = 0;
    if (iVar1 != 0) {
      printk("tm_mactable_add_set fail\n");
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

