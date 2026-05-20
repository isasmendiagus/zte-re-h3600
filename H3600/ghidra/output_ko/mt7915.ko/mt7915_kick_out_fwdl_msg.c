// module: mt7915.ko
// function: mt7915_kick_out_fwdl_msg @ 0x17c980
// size: 28 bytes
//

void mt7915_kick_out_fwdl_msg(int param_1)

{
  if (*(int *)(param_1 + 0xa7861c) != 2) {
    hif_kick_out_cmd_msg();
    return;
  }
  hif_kick_out_fwdl_msg();
  return;
}

