// module: mt7915.ko
// function: SetATEFixedPayload @ 0x262924
// size: 32 bytes
//

void SetATEFixedPayload(int param_1,undefined4 param_2)

{
  mt_agent_cli_set_dw("ATEFIXEDPAYLOAD",param_1 + 0xa77bb4,param_2);
  return;
}

