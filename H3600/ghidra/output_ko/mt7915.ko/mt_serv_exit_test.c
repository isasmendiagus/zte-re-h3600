// module: mt7915.ko
// function: mt_serv_exit_test @ 0x2506a4
// size: 76 bytes
//

undefined4 mt_serv_exit_test(int param_1)

{
  if (*(char *)(param_1 + 0x1f44) == '\0') {
    if (*(int *)(param_1 + 0x4e4) != 0) {
      sys_ad_free_mem();
      *(undefined4 *)(param_1 + 0x4e4) = 0;
    }
    if (*(int *)(param_1 + 0x11fc) != 0) {
      sys_ad_free_mem();
      *(undefined4 *)(param_1 + 0x11fc) = 0;
    }
  }
  return 0;
}

