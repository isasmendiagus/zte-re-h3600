// module: mt7915.ko
// function: show_vow_help @ 0x476f4
// size: 48 bytes
//

undefined4 show_vow_help(void)

{
  if (-1 < DebugLevel) {
    printk(
          "vow_rx_time (Non-wifi/OBSS)\nvow_sta_conf = <wlanidx>\nvow_sta_conf\nvow_bss_conf = <group>\nvow_all_bss_conf\nvow_dump_sta (raw)\nvow_dump_bss_bitmap (raw)\nvow_dump_bss (raw)\nvow_dump_vow (raw)\nvow_show_sta_dtoken = <wlanidx> DWRR\nvow_show_bss_dtoken = <group> DWRR\nvow_show_bss_atoken = <group> airtime\nvow_show_bss_ltoken = <group> length\n"
          );
  }
  return 1;
}

