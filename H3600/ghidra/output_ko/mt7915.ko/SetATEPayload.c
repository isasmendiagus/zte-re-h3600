// module: mt7915.ko
// function: SetATEPayload @ 0x262904
// size: 32 bytes
//

void SetATEPayload(int param_1,undefined4 param_2)

{
  mt_agent_cli_set_dw("ATEPAYLOAD",param_1 + 0xa77bb4,param_2);
  return;
}

