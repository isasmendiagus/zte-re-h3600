// module: mt7915.ko
// function: SetATETxMcs @ 0x261e50
// size: 32 bytes
//

void SetATETxMcs(int param_1,undefined4 param_2)

{
  mt_agent_cli_set_dw("ATETXMCS",param_1 + 0xa77bb4,param_2);
  return;
}

