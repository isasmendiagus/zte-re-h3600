// module: mt7915.ko
// function: SetATETxMode @ 0x261f6c
// size: 32 bytes
//

void SetATETxMode(int param_1,undefined4 param_2)

{
  mt_agent_cli_set_dw("ATETXMODE",param_1 + 0xa77bb4,param_2);
  return;
}

