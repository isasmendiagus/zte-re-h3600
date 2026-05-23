// module: mt7915.ko
// function: sta_os_completion_initialize @ 0x688a0
// size: 96 bytes
//

void sta_os_completion_initialize(int param_1)

{
  *(undefined4 *)(param_1 + 0x213234) = 0;
  __init_waitqueue_head(param_1 + 0x213238,"&x->wait",sta_cntl_api_ops);
  *(undefined4 *)(param_1 + 0x213244) = 0;
  __init_waitqueue_head(param_1 + 0x213248,"&x->wait",sta_cntl_api_ops);
  return;
}

