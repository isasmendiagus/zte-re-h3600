// module: mt7915.ko
// function: sae_group_deinit_ecc @ 0x20758c
// size: 152 bytes
//

void sae_group_deinit_ecc(int param_1)

{
  int local_14;
  int local_10;
  int local_c;
  
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_group_deinit_ecc");
  }
  local_14 = *(int *)(param_1 + 0x54);
  local_10 = *(int *)(param_1 + 0x58);
  local_c = *(int *)(param_1 + 0x5c);
  if (local_14 != 0) {
    ecc_point_free(&local_14);
  }
  if (local_10 != 0) {
    ecc_point_free(&local_10);
  }
  if (local_c != 0) {
    ecc_point_free(&local_c);
  }
  return;
}

