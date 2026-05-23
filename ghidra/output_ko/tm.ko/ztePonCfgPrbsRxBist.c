// module: tm.ko
// function: ztePonCfgPrbsRxBist @ 0x63e28
// size: 116 bytes
//

undefined4 ztePonCfgPrbsRxBist(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  serdes_set_rx_prbs_mode(param_1 + -1);
  if (param_2 == 1) {
    serdes_set_check_en_open();
    serdes_set_err_cnt_en_open();
  }
  else if (param_2 == 0) {
    serdes_set_check_en_disable();
    serdes_set_err_cnt_en_disable();
  }
  if (1 < g_tm_debug_level) {
    printk("%s PrbsMode=%d\n, RxBistEnable=%d\n","ztePonCfgPrbsRxBist",param_1,param_2,param_4);
  }
  return 0;
}

