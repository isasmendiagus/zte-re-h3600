// module: plat-zxylzb_9128S.ko
// function: pon_tm_bmu_alloc_bp @ 0x18668
// size: 296 bytes
//

uint pon_tm_bmu_alloc_bp(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  _raw_spin_lock_bh(&alloc_lock);
  if (bmu_alloc_timeout != 0) {
    uVar1 = *(uint *)(tm_base + 0x8014) & 1;
    if (uVar1 != 0) goto LAB_000186ec;
    uVar2 = *(uint *)(tm_base + 0x800c);
    bmu_alloc_timeout = 0;
    if ((int)uVar2 < 0) {
      bmu_alloc_timeout = uVar1;
      _raw_spin_unlock_bh(&alloc_lock);
      bmu_status._36_4_ = bmu_status._36_4_ + 1;
      return uVar2 & 0xffff;
    }
  }
  *(uint *)(tm_base + 0x8014) = *(uint *)(tm_base + 0x8014) | 1;
  iVar3 = 200;
  do {
    uVar1 = *(uint *)(tm_base + 0x8014) & 3;
    if (uVar1 == 0) {
      uVar2 = *(uint *)(tm_base + 0x800c);
      if ((int)uVar2 < 0) {
        _raw_spin_unlock_bh(&alloc_lock);
        bmu_alloc_timeout = uVar1;
        bmu_status._8_4_ = bmu_status._8_4_ + 1;
        return uVar2 & 0xffff;
      }
      break;
    }
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bmu_alloc_timeout = 1;
LAB_000186ec:
  _raw_spin_unlock_bh(&alloc_lock);
  bmu_status._0_4_ = bmu_status._0_4_ + 1;
  return 0xffffffff;
}

