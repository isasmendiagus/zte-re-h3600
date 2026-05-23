// module: tm.ko
// function: tm_mactable_lookup_get @ 0x4b49c
// size: 248 bytes
//

undefined4 tm_mactable_lookup_get(undefined4 *param_1)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 auStack_30 [4];
  int local_2c;
  int local_28;
  undefined4 local_24;
  undefined4 local_20;
  int local_1c;
  int local_18;
  undefined4 local_14;
  
  if (param_1 == (undefined4 *)0x0) {
    printk("ERROR:(%s:%d)","tm_api.c",0x3f5e);
    printk("param pp_entry is NULL\n");
    uVar3 = 0xffffffff;
  }
  else {
    local_20 = param_1[3];
    local_1c = (uint)*(byte *)(param_1 + 2) * 0x10000 +
               (uint)*(byte *)((int)param_1 + 9) * 0x1000000 +
               (uint)*(byte *)((int)param_1 + 7) * 0x100 + (uint)*(byte *)((int)param_1 + 6);
    local_18 = (uint)*(byte *)((int)param_1 + 10) + (uint)*(byte *)((int)param_1 + 0xb) * 0x100;
    iVar2 = sbrg_lookup_mactable(auStack_30);
    if (iVar2 == 0) {
      *(bool *)(param_1 + 1) = local_28 != 0;
      *(bool *)((int)param_1 + 5) = local_2c != 0;
      uVar1 = sbrg_change_portmask(local_14);
      *(undefined1 *)(param_1 + 4) = uVar1;
      *param_1 = local_24;
      uVar3 = 0;
    }
    else {
      printk("ERROR:(%s:%d)","tm_api.c",0x3f69);
      printk("tm_mactable_lookup_get fail\n");
      uVar3 = 0xffffffff;
    }
  }
  return uVar3;
}

