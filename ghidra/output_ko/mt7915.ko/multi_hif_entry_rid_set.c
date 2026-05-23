// module: mt7915.ko
// function: multi_hif_entry_rid_set @ 0x14e9a8
// size: 8 bytes
//

void multi_hif_entry_rid_set(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + -8) = param_2;
  return;
}

