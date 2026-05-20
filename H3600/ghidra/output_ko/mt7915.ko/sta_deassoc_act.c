// module: mt7915.ko
// function: sta_deassoc_act @ 0x687f8
// size: 20 bytes
//

void sta_deassoc_act(int param_1)

{
  RTEnqueueInternalCmd(*(undefined4 *)(param_1 + 8),0x1d,param_1,0x4060);
  return;
}

