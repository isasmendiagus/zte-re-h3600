// module: tm.ko
// function: tm_mactable_delete_set @ 0x4ce58
// size: 164 bytes
//

undefined4 tm_mactable_delete_set(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_28 [16];
  undefined4 local_18;
  int local_14;
  int local_10;
  
  if (param_1 == 0) {
    printk("ERROR:(%s:%d)","tm_api.c",0x3fb9);
    printk("param pp_entry is NULL\n");
    uVar2 = 0xffffffff;
  }
  else {
    local_18 = *(undefined4 *)(param_1 + 0xc);
    local_14 = (uint)*(byte *)(param_1 + 8) * 0x10000 + (uint)*(byte *)(param_1 + 9) * 0x1000000 +
               (uint)*(byte *)(param_1 + 7) * 0x100 + (uint)*(byte *)(param_1 + 6);
    local_10 = (uint)*(byte *)(param_1 + 10) + (uint)*(byte *)(param_1 + 0xb) * 0x100;
    iVar1 = sbrg_delete_mactable(auStack_28);
    uVar2 = 0;
    if (iVar1 != 0) {
      printk("tm_mactable_delete_set fail\n");
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

