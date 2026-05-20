// module: mt7915.ko
// function: mtf_rxv_handler @ 0x1a1060
// size: 56 bytes
//

undefined4 mtf_rxv_handler(undefined4 param_1,int param_2,int param_3)

{
  if (param_3 != 0 && param_2 != 0) {
    chip_parse_rxv_packet(param_1,1,param_2,param_3);
    return 0;
  }
  return 1;
}

