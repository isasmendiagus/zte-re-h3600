// module: mt7915.ko
// function: ap_cntl_init @ 0x4afc4
// size: 68 bytes
//

void ap_cntl_init(int param_1)

{
  *(undefined1 **)(param_1 + 0xe20) = ap_cntl_api_ops;
  ap_cntl_api_ops._0_4_ = ap_cntl_disconnect_proc;
  ap_cntl_api_ops._8_4_ = ap_cntl_scan;
  ap_cntl_api_ops._44_4_ = ap_cntl_scan_conf;
  ap_cntl_api_ops._48_4_ = ap_cntl_error_handle;
  return;
}

