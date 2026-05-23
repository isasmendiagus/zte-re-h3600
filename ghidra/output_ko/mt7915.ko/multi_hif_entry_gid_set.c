// module: mt7915.ko
// function: multi_hif_entry_gid_set @ 0x14e9a0
// size: 8 bytes
//

void multi_hif_entry_gid_set(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + -0xc) = param_2;
  return;
}

