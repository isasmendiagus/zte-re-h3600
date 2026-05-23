// module: mt7915.ko
// function: SetATETxNss @ 0x261e70
// size: 32 bytes
//

void SetATETxNss(int param_1,undefined4 param_2)

{
  mt_agent_cli_set_dw("ATETXNSS",param_1 + 0xa77bb4,param_2);
  return;
}

