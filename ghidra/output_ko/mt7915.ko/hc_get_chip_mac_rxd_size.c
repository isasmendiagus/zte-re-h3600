// module: mt7915.ko
// function: hc_get_chip_mac_rxd_size @ 0xa899c
// size: 8 bytes
//

undefined1 hc_get_chip_mac_rxd_size(int param_1)

{
  return *(undefined1 *)(param_1 + 0xb37);
}

