// module: mt7915.ko
// function: ba_timeout_monitor @ 0xa57c8
// size: 252 bytes
//

void ba_timeout_monitor(int param_1)

{
  uint uVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  code *pcVar6;
  uint uVar7;
  int iVar8;
  
  if (*(char *)(param_1 + 0x2f5ec) != '\0') {
    return;
  }
  iVar8 = 10 - jiffies;
  uVar4 = 0;
  bVar2 = false;
  iVar5 = param_1;
  do {
    while (((*(int *)(iVar5 + 0x1c8) != 4 || (*(int *)(iVar5 + 500) < 1)) ||
           (-1 < iVar8 + *(int *)(iVar5 + 0x1d8)))) {
      uVar4 = uVar4 + 1;
      iVar5 = iVar5 + 0x60;
      if (uVar4 == 0x480) goto LAB_000a5860;
    }
    uVar1 = uVar4 >> 5;
    uVar7 = uVar4 & 0x1f;
    uVar4 = uVar4 + 1;
    bVar2 = true;
    iVar3 = param_1 + uVar1 * 4;
    iVar5 = iVar5 + 0x60;
    *(uint *)(iVar3 + 0x2f5f0) = *(uint *)(iVar3 + 0x2f5f0) | 1 << uVar7;
  } while (uVar4 != 0x480);
LAB_000a5860:
  if (bVar2) {
    if ((*(uint *)(param_1 + 0x286280) & 0xfffffffb) == 1) {
      iVar5 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
      iVar8 = *(int *)(iVar5 + 0xa0);
      iVar5 = *(int *)(iVar8 + 0x6c0);
      uVar4 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
      if ((uVar4 & 0x8000) == 0) {
        pcVar6 = *(code **)(iVar5 + 4);
      }
      else {
        pcVar6 = *(code **)(iVar5 + 0xc);
      }
      (*pcVar6)(iVar8 + 0xe0);
    }
    *(undefined1 *)(param_1 + 0x2f5ec) = 1;
    return;
  }
  return;
}

