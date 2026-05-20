// module: mt7915.ko
// function: traversal_func_find_entry_by_aid @ 0x14c080
// size: 28 bytes
//

bool traversal_func_find_entry_by_aid(int param_1,short *param_2)

{
  bool bVar1;
  
  bVar1 = *param_2 == *(short *)(param_1 + 0xf8);
  if (bVar1) {
    *(int *)(param_2 + 2) = param_1;
  }
  return bVar1;
}

