// module: plat-zxylzb_9128S.ko
// function: pp_bmu_free_bp @ 0x18794
// size: 204 bytes
//

undefined4 pp_bmu_free_bp(uint param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  
  _raw_spin_lock_bh(&free_lock);
  iVar1 = 200;
  do {
    if (allow_free_cnt != 0) {
      allow_free_cnt = allow_free_cnt - 1;
      if (param_3 != 0) {
        bmu_status._16_4_ = bmu_status._16_4_ + 1;
      }
      bmu_status._12_4_ = bmu_status._12_4_ + 1;
      *(uint *)(tm_base + 0x8010) = param_1 | param_3 << 0xf;
      _raw_spin_unlock_bh(&free_lock);
      return 0;
    }
    iVar1 = iVar1 + -1;
    allow_free_cnt = (uint)(*(int *)(tm_base + 0x80dc) << 0x17) >> 0x1a;
  } while (iVar1 != 0);
  _raw_spin_unlock_bh(&free_lock);
  bmu_status._4_4_ = bmu_status._4_4_ + 1;
  return 0xffffffff;
}

