// module: mt7915.ko
// function: hc_get_phy_cap @ 0xaab90
// size: 8 bytes
//

undefined4 hc_get_phy_cap(int param_1)

{
  return *(undefined4 *)(param_1 + 0xb60);
}

