// module: mt7915.ko
// function: set_ate_control_band_idx @ 0x263dc0
// size: 32 bytes
//

void set_ate_control_band_idx(int param_1,undefined4 param_2)

{
  mt_agent_cli_set_ext("ATECTRLBANDIDX",param_1 + 0xa77bb4,param_2);
  return;
}

