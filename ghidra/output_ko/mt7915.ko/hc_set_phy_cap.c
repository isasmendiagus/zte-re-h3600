// module: mt7915.ko
// function: hc_set_phy_cap @ 0xaabb8
// size: 16 bytes
//

void hc_set_phy_cap(int param_1,uint param_2)

{
  *(uint *)(param_1 + 0xb60) = *(uint *)(param_1 + 0xb60) | param_2;
  return;
}

