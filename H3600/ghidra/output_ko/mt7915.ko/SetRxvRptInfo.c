// module: mt7915.ko
// function: SetRxvRptInfo @ 0xc0d14
// size: 16 bytes
//

undefined4 SetRxvRptInfo(void)

{
  chip_rxv_dump_show_rpt();
  return 1;
}

