// module: mt7915.ko
// function: hc_show_edca_info @ 0xa96f0
// size: 12 bytes
//

void hc_show_edca_info(int param_1)

{
  wmm_ctrl_show_entry(param_1 + 0x1a08);
  return;
}

