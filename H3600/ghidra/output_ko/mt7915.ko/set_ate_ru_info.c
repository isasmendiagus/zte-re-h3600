// module: mt7915.ko
// function: set_ate_ru_info @ 0x262074
// size: 32 bytes
//

void set_ate_ru_info(int param_1,undefined4 param_2)

{
  mt_agent_cli_set_ext("ATERUINFO",param_1 + 0xa77bb4,param_2);
  return;
}

