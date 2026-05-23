// module: mt7915.ko
// function: SetATEChannel @ 0x26be28
// size: 32 bytes
//

void SetATEChannel(int param_1,undefined4 param_2)

{
  mt_agent_cli_set_ext("ATECHANNEL",param_1 + 0xa77bb4,param_2);
  return;
}

