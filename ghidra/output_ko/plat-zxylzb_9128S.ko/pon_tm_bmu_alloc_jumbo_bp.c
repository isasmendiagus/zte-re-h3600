// module: plat-zxylzb_9128S.ko
// function: pon_tm_bmu_alloc_jumbo_bp @ 0x18868
// size: 232 bytes
//

uint pon_tm_bmu_alloc_jumbo_bp(void)

{
  int iVar1;
  uint uVar2;
  
  if ((*(uint *)(tm_base + 0x8014) & 1) != 0) {
    bmu_status._0_4_ = bmu_status._0_4_ + 1;
    return 0xffffffff;
  }
  _raw_spin_lock_bh(&alloc_lock);
  *(undefined4 *)(tm_base + 0x8014) = 3;
  iVar1 = 200;
  do {
    if ((*(uint *)(tm_base + 0x8014) & 1) == 0) {
      uVar2 = *(uint *)(tm_base + 0x800c);
      if ((int)uVar2 < 0) {
        _raw_spin_unlock_bh(&alloc_lock);
        bmu_status._8_4_ = bmu_status._8_4_ + 1;
        return uVar2 & 0xffff;
      }
      break;
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  _raw_spin_unlock_bh(&alloc_lock);
  bmu_status._0_4_ = bmu_status._0_4_ + 1;
  return 0xffffffff;
}

