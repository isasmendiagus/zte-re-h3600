// module: mt7915.ko
// function: is_pmkid_cache_in_sec_config @ 0x117384
// size: 44 bytes
//

bool is_pmkid_cache_in_sec_config(int param_1)

{
  if (param_1 == 0) {
    return false;
  }
  if (*(int *)(param_1 + 0x58c) != 0) {
    return *(int *)(param_1 + 0x590) != 0;
  }
  return false;
}

