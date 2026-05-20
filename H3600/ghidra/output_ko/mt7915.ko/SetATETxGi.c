// module: mt7915.ko
// function: SetATETxGi @ 0x261f8c
// size: 32 bytes
//

void SetATETxGi(int param_1,undefined4 param_2)

{
  mt_agent_cli_set_dw("ATETXGI",param_1 + 0xa77bb4,param_2);
  return;
}

