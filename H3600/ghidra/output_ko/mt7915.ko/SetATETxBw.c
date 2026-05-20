// module: mt7915.ko
// function: SetATETxBw @ 0x26c6a0
// size: 32 bytes
//

void SetATETxBw(int param_1,undefined4 param_2)

{
  mt_agent_cli_set_ext("ATETXBW",param_1 + 0xa77bb4,param_2);
  return;
}

