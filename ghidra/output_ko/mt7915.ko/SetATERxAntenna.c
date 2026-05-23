// module: mt7915.ko
// function: SetATERxAntenna @ 0x261b80
// size: 32 bytes
//

void SetATERxAntenna(int param_1,undefined4 param_2)

{
  mt_agent_cli_set_ext("ATERXANT",param_1 + 0xa77bb4,param_2);
  return;
}

