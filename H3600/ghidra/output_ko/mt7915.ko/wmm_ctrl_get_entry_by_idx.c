// module: mt7915.ko
// function: wmm_ctrl_get_entry_by_idx @ 0xad190
// size: 20 bytes
//

int wmm_ctrl_get_entry_by_idx(int param_1,int param_2)

{
  return *(int *)(param_1 + 0x1a0c) + param_2 * 0x28;
}

