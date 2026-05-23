// module: mt7915.ko
// function: release_temporal_usage_big_interger @ 0x1fb11c
// size: 72 bytes
//

void release_temporal_usage_big_interger(int *param_1)

{
  if ((*param_1 != 0) && (*(char *)(*param_1 + 0x20) == '\x01')) {
    _raw_spin_lock_bh(&bi_pool_lock);
    *(undefined1 *)(*param_1 + 0x20) = 0;
    *param_1 = 0;
    _raw_spin_unlock_bh(&bi_pool_lock);
    return;
  }
  BigInteger_Free();
  return;
}

