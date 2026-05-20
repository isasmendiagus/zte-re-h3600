// module: mt7915.ko
// function: bcolor_update_by_bitmap @ 0x16b2d8
// size: 156 bytes
//

void bcolor_update_by_bitmap(int param_1,int param_2,void *param_3)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  byte local_20 [12];
  
  iVar2 = RcGetBandIdx(*(undefined4 *)(param_2 + 8));
  uVar1 = jiffies;
  os_move_mem(local_20,param_3,8);
  iVar5 = param_1 + iVar2 * 0x100 + 0x31d4;
  _raw_spin_lock_bh(iVar5);
  uVar4 = 1;
  puVar6 = (undefined4 *)(param_1 + iVar2 * 0x100 + 0x30d8);
  do {
    uVar3 = uVar4 & 7;
    iVar2 = (int)uVar4 >> 3;
    uVar4 = uVar4 + 1;
    if (((int)(uint)local_20[iVar2] >> uVar3 & 1U) != 0) {
      *puVar6 = uVar1;
    }
    puVar6 = puVar6 + 1;
  } while (uVar4 != 0x40);
  _raw_spin_unlock_bh(iVar5);
  return;
}

