// module: mt7915.ko
// function: sta_fsm_ops_hook @ 0x68cd4
// size: 32 bytes
//

void sta_fsm_ops_hook(undefined4 param_1)

{
  sta_cntl_init();
  sta_auth_init(param_1);
  sta_assoc_init(param_1);
  return;
}

