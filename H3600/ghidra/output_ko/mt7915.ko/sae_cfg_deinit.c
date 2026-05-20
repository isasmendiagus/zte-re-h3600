// module: mt7915.ko
// function: sae_cfg_deinit @ 0x208cac
// size: 100 bytes
//

void sae_cfg_deinit(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = hc_get_chip_wtbl_max_num(*(undefined4 *)(*(int *)(param_2 + 0x1b924) + 0xa797a0));
  if (iVar1 == 0) {
    return;
  }
  iVar2 = 0;
  do {
    while (iVar2 = iVar2 + 1, *(char *)(param_2 + 0x128) == '\0') {
      param_2 = param_2 + 0x188;
      if (iVar2 == iVar1) {
        return;
      }
    }
    delete_sae_instance(param_2);
    param_2 = param_2 + 0x188;
  } while (iVar2 != iVar1);
  return;
}

