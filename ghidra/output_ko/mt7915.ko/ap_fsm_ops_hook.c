// module: mt7915.ko
// function: ap_fsm_ops_hook @ 0x1707c
// size: 32 bytes
//

void ap_fsm_ops_hook(undefined4 param_1)

{
  ap_cntl_init();
  ap_auth_init(param_1);
  ap_assoc_init(param_1);
  return;
}

