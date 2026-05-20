// module: mt7915.ko
// function: SetATETxAntenna @ 0x261b60
// size: 32 bytes
//

void SetATETxAntenna(int param_1,undefined4 param_2)

{
  mt_agent_cli_set_ext("ATETXANT",param_1 + 0xa77bb4,param_2);
  return;
}

