// module: mt7915.ko
// function: SetATETxPower0 @ 0x2615cc
// size: 32 bytes
//

void SetATETxPower0(int param_1,undefined4 param_2)

{
  mt_agent_cli_set_ext("ATETXPOW0",param_1 + 0xa77bb4,param_2);
  return;
}

