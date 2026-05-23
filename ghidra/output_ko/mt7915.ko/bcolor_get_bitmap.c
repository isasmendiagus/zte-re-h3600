// module: mt7915.ko
// function: bcolor_get_bitmap @ 0x16b230
// size: 168 bytes
//

void bcolor_get_bitmap(int param_1,int param_2,void *param_3)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  byte local_20 [12];
  
  iVar2 = RcGetBandIdx(*(undefined4 *)(param_2 + 8));
  iVar2 = iVar2 * 0x100;
  os_zero_mem(local_20,8);
  iVar6 = param_1 + iVar2 + 0x31d4;
  _raw_spin_lock_bh(iVar6);
  uVar5 = 1;
  piVar3 = (int *)(param_1 + iVar2 + 0x30d4);
  do {
    piVar3 = piVar3 + 1;
    iVar1 = (int)uVar5 >> 3;
    uVar4 = uVar5 & 7;
    uVar5 = uVar5 + 1;
    if (*piVar3 != 0) {
      local_20[iVar1] = local_20[iVar1] | (byte)(1 << uVar4);
    }
  } while (piVar3 != (int *)(param_1 + iVar2 + 0x31d0));
  _raw_spin_unlock_bh(iVar6);
  os_move_mem(param_3,local_20,8);
  return;
}

