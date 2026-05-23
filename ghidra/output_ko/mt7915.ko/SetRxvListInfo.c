// module: mt7915.ko
// function: SetRxvListInfo @ 0xc0d04
// size: 16 bytes
//

undefined4 SetRxvListInfo(void)

{
  chip_rxv_dump_show_list();
  return 1;
}

