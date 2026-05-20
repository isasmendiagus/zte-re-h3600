// module: mt7915.ko
// function: wdev_fsm_init @ 0x14de78
// size: 92 bytes
//

void wdev_fsm_init(int param_1)

{
  sync_fsm_ops_init();
  cntl_state_machine_init(param_1,param_1 + 0xc9c,param_1 + 0xcb4);
  auth_fsm_init(*(undefined4 *)(param_1 + 8),param_1,param_1 + 0xe24,param_1 + 0xe3c);
  assoc_fsm_init(*(undefined4 *)(param_1 + 8),param_1,param_1 + 0xbd0,param_1 + 0xbe8);
  return;
}

