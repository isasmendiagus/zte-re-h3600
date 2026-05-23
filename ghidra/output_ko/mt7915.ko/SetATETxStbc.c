// module: mt7915.ko
// function: SetATETxStbc @ 0x261f4c
// size: 32 bytes
//

void SetATETxStbc(int param_1,undefined4 param_2)

{
  mt_agent_cli_set_dw("ATETXSTBC",param_1 + 0xa77bb4,param_2);
  return;
}

