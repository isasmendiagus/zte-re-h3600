// module: mt7915.ko
// function: sta_deauth_act @ 0x687e4
// size: 20 bytes
//

void sta_deauth_act(int param_1)

{
  RTEnqueueInternalCmd(*(undefined4 *)(param_1 + 8),0x1c,param_1,0x4060);
  return;
}

