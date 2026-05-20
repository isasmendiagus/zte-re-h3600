// module: mt7915.ko
// function: mt_service_init @ 0x13d14c
// size: 572 bytes
//

undefined4 mt_service_init(int param_1)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 *puVar4;
  int iVar5;
  int *piVar6;
  
  puVar1 = (undefined1 *)hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar2 = hc_get_ct_cb(*(undefined4 *)(param_1 + 0xa797a0));
  iVar3 = token_tx_get_queue_by_band(uVar2,0);
  puVar4 = (undefined1 *)hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  piVar6 = *(int **)(param_1 + 0xa77bb8);
  iVar5 = *piVar6;
  *(undefined4 *)(iVar5 + 4) = *(undefined4 *)(param_1 + 4);
  *(undefined4 *)(*piVar6 + 8) = *(undefined4 *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc);
  *(undefined4 *)(*piVar6 + 0x30) = *(undefined4 *)(param_1 + 0xa797a0);
  *(undefined1 *)(*piVar6 + 0x34) = *(undefined1 *)(param_1 + 0x79504d);
  *(undefined4 *)(*piVar6 + 0x38) = *(undefined4 *)(iVar3 + 0x10);
  *(undefined1 *)(*piVar6 + 0x71) = puVar1[0x150];
  *(undefined1 *)(iVar5 + 0x70) = puVar1[0x20];
  *(undefined1 *)(iVar5 + 0x3c) = *puVar1;
  *(undefined1 *)(iVar5 + 0x3d) = puVar1[1];
  *(undefined1 *)(iVar5 + 0x3e) = puVar1[2];
  *(undefined1 *)(iVar5 + 0x3f) = puVar1[3];
  *(undefined1 *)(iVar5 + 0x40) = *puVar4;
  *(undefined1 *)(iVar5 + 0x41) = puVar4[1];
  *(undefined2 *)(iVar5 + 0x42) = *(undefined2 *)(puVar1 + 4);
  *(undefined1 *)(iVar5 + 0x44) = puVar1[0x5f];
  *(undefined2 *)(iVar5 + 0x46) = *(undefined2 *)(puVar1 + 0x52);
  *(undefined1 *)(iVar5 + 0x48) = puVar1[0x60];
  *(undefined1 *)(iVar5 + 0x49) = puVar1[0x61];
  *(undefined1 *)(iVar5 + 0x4c) = puVar1[100];
  *(undefined2 *)(iVar5 + 0x4a) = *(undefined2 *)(puVar1 + 0x4e);
  *(uint *)(iVar5 + 0x50) = (uint)*(ushort *)(puVar1 + 0xf4);
  if ((*(uint *)(puVar1 + 0x2c) & 0x800000) != 0) {
    *(undefined1 *)(iVar5 + 0x72) = 1;
  }
  *(char *)(*piVar6 + 0x74) = "Set_IRR_TTGOnOff"[param_1 + 1];
  *(char *)(*piVar6 + 0x75) = "cp_support_is_enabled"[param_1 + 5];
  *(char *)(*piVar6 + 0x76) = "cp_support_is_enabled"[param_1 + 4];
  if (("cp_support_is_enabled"[param_1 + 5] - 2U & 0xfd) == 0) {
    uVar2 = get_dev_eeprom_size(param_1);
    *(undefined4 *)(iVar5 + 0x50) = uVar2;
  }
  os_move_mem((void *)(*piVar6 + 0x68),puVar1 + 0x21c,8);
  os_move_mem((void *)(*piVar6 + 0xc),(void *)(param_1 + 0xa78548),0x24);
  os_move_mem((void *)(*piVar6 + 0x54),puVar1 + 0x6c,6);
  os_move_mem((void *)(*piVar6 + 0x58),puVar1 + 0x74,0x10);
  iVar3 = mt_agent_init_service(param_1 + 0xa77bb4);
  if (iVar3 == 0) {
    if (0 < DebugLevel) {
      printk("%s: wlan service inits successfully!\n","mt_service_init");
      return 0;
    }
    return 0;
  }
  if (-1 < DebugLevel) {
    printk("%s: wlan service inits failed!\n","mt_service_init");
  }
  mt_agent_exit_service(param_1 + 0xa77bb4);
  return 1;
}

