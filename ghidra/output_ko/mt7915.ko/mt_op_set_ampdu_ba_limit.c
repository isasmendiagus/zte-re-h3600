// module: mt7915.ko
// function: mt_op_set_ampdu_ba_limit @ 0x2578ac
// size: 28 bytes
//

undefined4 mt_op_set_ampdu_ba_limit(void)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = mt_test_mac_set_ampdu_ba_limit();
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = 0x502;
  }
  return uVar2;
}

