// module: mt7915.ko
// function: set_txbf_stop_report_poll_proc @ 0xe58b8
// size: 128 bytes
//

undefined4 set_txbf_stop_report_poll_proc(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  byte local_e [6];
  
  local_e[0] = os_str_tol(param_2,0,10);
  if (1 < local_e[0]) {
    if (0 < DebugLevel) {
      printk(
            "Wrong format!\niwpirv ra0 set TxBfStopReportPoll=N\nN=1: Stop Rpt Poll\nN=0: Re-enable Rpt Poll\n"
            );
    }
    return 0;
  }
  local_e[1] = 0;
  uVar1 = txbf_config(param_1,0,local_e);
  return uVar1;
}

