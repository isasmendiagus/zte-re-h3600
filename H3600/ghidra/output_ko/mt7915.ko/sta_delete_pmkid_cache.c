// module: mt7915.ko
// function: sta_delete_pmkid_cache @ 0x6b768
// size: 252 bytes
//

void sta_delete_pmkid_cache(int param_1,undefined4 param_2,int param_3,int param_4)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  
  if (*(int *)(param_4 + 0x14) == 0x100) {
    iVar1 = *(int *)(param_4 + 4);
    iVar3 = iVar1 + 0x414c;
    piVar2 = (int *)(iVar1 + 0x42a8);
    piVar4 = (int *)(iVar1 + 0x42ac);
  }
  else {
    piVar2 = (int *)(&DAT_00580300 + param_1 + param_3 * 0x2137b0);
    iVar3 = param_1 + param_3 * 0x2137b0 + 0x5801a1;
    piVar4 = piVar2 + 1;
  }
  iVar1 = sta_search_pmkid_cache();
  if (iVar1 == -1) {
    return;
  }
  if (piVar4 == (int *)0x0) {
    iVar3 = iVar3 + iVar1 * 0x57;
    if (*(char *)(iVar3 + 0x56) == '\x01') {
      *(undefined1 *)(iVar3 + 0x56) = 0;
      if (*piVar2 != 0) {
        *piVar2 = *piVar2 + -1;
      }
      return;
    }
    return;
  }
  _raw_spin_lock_bh(piVar4);
  iVar3 = iVar3 + iVar1 * 0x57;
  if (*(char *)(iVar3 + 0x56) == '\x01') {
    *(undefined1 *)(iVar3 + 0x56) = 0;
    if (*piVar2 != 0) {
      *piVar2 = *piVar2 + -1;
    }
    _raw_spin_unlock_bh(piVar4);
    return;
  }
  _raw_spin_unlock_bh(piVar4);
  return;
}

