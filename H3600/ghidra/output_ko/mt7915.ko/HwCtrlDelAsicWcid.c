// module: mt7915.ko
// function: HwCtrlDelAsicWcid @ 0xaef9c
// size: 92 bytes
//

undefined4 HwCtrlDelAsicWcid(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = **(uint **)(param_2 + 8);
  uVar1 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (uVar2 == 0x7fff || uVar2 < uVar1) {
    AsicDelWcidTab(param_1,uVar2 & 0xffff);
    return 0;
  }
  return 1;
}

