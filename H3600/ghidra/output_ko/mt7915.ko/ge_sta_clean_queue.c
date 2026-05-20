// module: mt7915.ko
// function: ge_sta_clean_queue @ 0xd0cb0
// size: 528 bytes
//

undefined4 ge_sta_clean_queue(int param_1,uint param_2)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  uint local_34;
  
  if (param_2 == 0x7fff) {
    param_2 = 0;
    iVar4 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    local_34 = iVar4 - 1U & 0xffff;
  }
  else {
    uVar1 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    local_34 = param_2;
    if (uVar1 <= param_2 || 0x11f < param_2) {
      if (0 < DebugLevel) {
        printk("%s():Invalid WCID[%d]\n","ge_sta_clean_queue",param_2);
      }
      return 0;
    }
  }
  do {
    iVar4 = param_2 * 0x620;
    if (*(int *)(param_1 + iVar4 + 0x2f6a0) != 0) {
      puVar6 = (undefined4 *)(param_1 + iVar4 + 0x2f6c8);
      iVar5 = param_1 + iVar4 + 0x2f734;
      do {
        _raw_spin_lock_bh(iVar5);
        piVar2 = (int *)puVar6[-1];
        if (piVar2 != (int *)0x0) {
          iVar3 = param_1 + param_2 * 0x620;
          do {
            iVar7 = *piVar2;
            *piVar2 = 0;
            puVar6[-1] = iVar7;
            if (iVar7 == 0) {
              *puVar6 = 0;
            }
            puVar6[1] = puVar6[1] + -1;
            *(int *)(iVar3 + 0x2f714) = *(int *)(iVar3 + 0x2f714) + -1;
            RTMPFreeNdisPacket(param_1,piVar2);
            piVar2 = (int *)puVar6[-1];
          } while (piVar2 != (int *)0x0);
        }
        puVar6 = puVar6 + 4;
        _raw_spin_unlock_bh(iVar5);
        iVar5 = iVar5 + 4;
      } while (puVar6 != (undefined4 *)(param_1 + iVar4 + 0x2f708));
      iVar4 = param_1 + param_2 * 0x620;
      iVar5 = param_1 + param_2 * 0x620 + 0x2f744;
      _raw_spin_lock_bh(iVar5);
      piVar2 = *(int **)(iVar4 + 0x2f704);
      while (piVar2 != (int *)0x0) {
        iVar3 = *piVar2;
        *piVar2 = 0;
        if (iVar3 == 0) {
          *(undefined4 *)(iVar4 + 0x2f708) = 0;
        }
        *(int *)(iVar4 + 0x2f704) = iVar3;
        *(int *)(iVar4 + 0x2f70c) = *(int *)(iVar4 + 0x2f70c) + -1;
        RTMPFreeNdisPacket(param_1,piVar2);
        piVar2 = *(int **)(iVar4 + 0x2f704);
      }
      _raw_spin_unlock_bh(iVar5);
    }
    param_2 = param_2 + 1 & 0xffff;
  } while (param_2 <= local_34);
  return 0;
}

