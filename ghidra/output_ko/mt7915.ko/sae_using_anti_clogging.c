// module: mt7915.ko
// function: sae_using_anti_clogging @ 0x2092a0
// size: 244 bytes
//

undefined4 sae_using_anti_clogging(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  
  iVar1 = hc_get_chip_wtbl_max_num(*(undefined4 *)(*(int *)(param_1 + 0x1b924) + 0xa797a0));
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_using_anti_clogging");
  }
  if (*(uint *)(param_1 + 0x1b908) < *(uint *)(param_1 + 0x1b918)) {
    return 0;
  }
  iVar5 = param_1 + 0x1b928;
  _raw_spin_lock_bh(iVar5);
  if (iVar1 != 0) {
    uVar2 = 0;
    pcVar4 = (char *)(param_1 + 0x128);
    iVar6 = 0;
    iVar3 = 0;
    do {
      iVar3 = iVar3 + 1;
      if (*pcVar4 != '\0') {
        iVar6 = iVar6 + 1;
        if (*(int *)(pcVar4 + -0x128) - 1U < 2) {
          uVar2 = uVar2 + 1;
        }
        if (*(uint *)(param_1 + 0x1b918) <= uVar2) {
          _raw_spin_unlock_bh(iVar5);
          return 1;
        }
        if (*(int *)(param_1 + 0x1b908) == iVar6) break;
      }
      pcVar4 = pcVar4 + 0x188;
    } while (iVar3 != iVar1);
  }
  _raw_spin_unlock_bh(iVar5);
  return 0;
}

