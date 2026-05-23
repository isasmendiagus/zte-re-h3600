// module: mt7915.ko
// function: MT_ATESetRxUserIdx @ 0x27e984
// size: 84 bytes
//

void MT_ATESetRxUserIdx(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  if (0 < DebugLevel) {
    printk("%s(): band_idx: %d, user_idx: 0x%x\n","MT_ATESetRxUserIdx",param_2,param_3);
  }
  mt_cmd_set_rx_stat_user_idx(param_1,param_2,param_3);
  return;
}

