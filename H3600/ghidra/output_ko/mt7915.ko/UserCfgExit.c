// module: mt7915.ko
// function: UserCfgExit @ 0x13a56c
// size: 268 bytes
//

void UserCfgExit(int param_1)

{
  int *piVar1;
  
  entrytb_aid_bitmap_free(param_1 + 0x28594c);
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    (&DAT_0036b830)[param_1] = 0;
    (&DAT_0036b844)[param_1] = 0;
    complete_all(&DAT_0036b834 + param_1);
    if ((&DAT_0036b920)[param_1] != '\0') {
      BndStrg_Release(param_1);
    }
  }
  piVar1 = (int *)(s_TotalTimeForDump_0x_x____d_secs__00371a28 + param_1 + 8);
  do {
    if (piVar1[-0xd68] != 0) {
      os_free_mem();
      piVar1[-0xd68] = 0;
    }
    if (piVar1[-4] != 0) {
      os_free_mem();
    }
    piVar1[-4] = 0;
    if (*piVar1 != 0) {
      os_free_mem();
    }
    *piVar1 = 0;
    piVar1 = piVar1 + 0x84dec;
  } while (piVar1 != (int *)(param_1 + 0x798990));
  wdev_config_init(param_1);
  sae_cfg_deinit(param_1,"pci_sw_int_handler" + param_1);
  group_info_bi_deinit();
  sae_pwd_id_deinit(param_1);
  scan_release_mem(param_1);
  return;
}

