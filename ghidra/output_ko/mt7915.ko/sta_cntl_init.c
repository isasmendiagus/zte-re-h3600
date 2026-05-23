// module: mt7915.ko
// function: sta_cntl_init @ 0x750a4
// size: 176 bytes
//

void sta_cntl_init(int param_1)

{
  *(undefined1 **)(param_1 + 0xe20) = sta_cntl_api_ops;
  sta_cntl_api_ops._4_4_ = sta_cntl_connect_proc;
  sta_cntl_api_ops._0_4_ = sta_cntl_disconnect_proc;
  sta_cntl_api_ops._16_4_ = sta_cntl_join_conf;
  sta_cntl_api_ops._20_4_ = sta_cntl_auth_conf;
  sta_cntl_api_ops._24_4_ = sta_cntl_auth2_conf;
  sta_cntl_api_ops._28_4_ = sta_cntl_deauth_conf;
  sta_cntl_api_ops._32_4_ = sta_cntl_assoc_conf;
  sta_cntl_api_ops._36_4_ = sta_cntl_reassoc_conf;
  sta_cntl_api_ops._40_4_ = sta_cntl_disassoc_conf;
  sta_cntl_api_ops._8_4_ = sta_cntl_scan;
  sta_cntl_api_ops._44_4_ = sta_cntl_scan_conf;
  sta_cntl_api_ops._48_4_ = sta_cntl_error_handle;
  sta_cntl_api_ops._12_4_ = sta_cntl_reset_all_fsm;
  return;
}

