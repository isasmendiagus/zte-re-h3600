// module: mt7915.ko
// function: show_vow_watf_info @ 0x47fa0
// size: 404 bytes
//

undefined4 show_vow_watf_info(int param_1)

{
  uint uVar1;
  uint *puVar2;
  int iVar3;
  uint *puVar4;
  int iVar5;
  uint uVar6;
  undefined1 uStack_25;
  undefined1 local_22;
  undefined1 uStack_21;
  
  if ((((-1 < DebugLevel) && (printk("======== WATF Information ========\n"), -1 < DebugLevel)) &&
      (printk("vow_watf_en: %d\n",*(undefined1 *)(param_1 + 0xa7a32c)), -1 < DebugLevel)) &&
     (((printk("vow_watf_q_lv0: %d\n",*(undefined1 *)(param_1 + 0xa7a32d)), -1 < DebugLevel &&
       (printk("vow_watf_q_lv1: %d\n",*(undefined1 *)(param_1 + 0xa7a32e)), -1 < DebugLevel)) &&
      (printk("vow_watf_q_lv2: %d\n",*(undefined1 *)(param_1 + 0xa7a32f)), -1 < DebugLevel)))) {
    printk("vow_watf_q_lv3: %d\n",*(undefined1 *)(param_1 + 0xa7a330));
  }
  iVar5 = 0;
  puVar4 = (uint *)(param_1 + 0xa7a332);
  do {
    if (-1 < DebugLevel) {
      printk("======== WATF LV%d\'s MAC Address List ========\n",iVar5);
    }
    uVar6 = (uint)*(byte *)((int)puVar4 + -1);
    if (uVar6 != 0) {
      iVar3 = 0;
      puVar2 = puVar4;
      do {
        uVar1 = *puVar2;
        if (-1 < DebugLevel) {
          uStack_21 = (undefined1)((ushort)(short)puVar2[1] >> 8);
          local_22 = (undefined1)(short)puVar2[1];
          uStack_25 = (undefined1)(uVar1 >> 8);
          printk("Entry %d: %02x:%02x:%02x:%02x:%02x:%02x\n",iVar3,uVar1 & 0xff,uStack_25,
                 uVar1 >> 0x10 & 0xff,uVar1 >> 0x18,local_22,uStack_21);
          uVar6 = (uint)*(byte *)((int)puVar4 + -1);
        }
        iVar3 = iVar3 + 1;
        puVar2 = (uint *)((int)puVar2 + 6);
      } while (iVar3 < (int)uVar6);
    }
    iVar5 = iVar5 + 1;
    puVar4 = (uint *)((int)puVar4 + 0x6c1);
  } while (iVar5 != 4);
  return 1;
}

