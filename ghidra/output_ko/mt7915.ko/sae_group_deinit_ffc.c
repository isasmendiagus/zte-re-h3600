// module: mt7915.ko
// function: sae_group_deinit_ffc @ 0x207300
// size: 180 bytes
//

void sae_group_deinit_ffc(int param_1)

{
  int local_14;
  int local_10;
  int local_c;
  
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_group_deinit_ffc");
  }
  local_14 = *(int *)(param_1 + 0x54);
  local_10 = *(int *)(param_1 + 0x58);
  local_c = *(int *)(param_1 + 0x5c);
  if (local_14 != 0) {
    Bignum_Free(&local_14);
  }
  *(undefined4 *)(param_1 + 0x54) = 0;
  if (local_10 != 0) {
    Bignum_Free(&local_10);
  }
  *(undefined4 *)(param_1 + 0x58) = 0;
  if (local_c != 0) {
    Bignum_Free(&local_c);
  }
  *(undefined4 *)(param_1 + 0x5c) = 0;
  return;
}

