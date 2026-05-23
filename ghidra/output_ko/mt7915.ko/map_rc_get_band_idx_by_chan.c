// module: mt7915.ko
// function: map_rc_get_band_idx_by_chan @ 0x16029c
// size: 32 bytes
//

bool map_rc_get_band_idx_by_chan(int param_1,uint param_2)

{
  return *(char *)(param_1 + 0x79504d) != '\0' && 0xe < param_2;
}

