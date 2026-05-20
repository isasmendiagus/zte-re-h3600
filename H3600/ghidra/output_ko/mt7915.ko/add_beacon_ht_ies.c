// module: mt7915.ko
// function: add_beacon_ht_ies @ 0x139a9c
// size: 40 bytes
//

undefined4 add_beacon_ht_ies(int param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  
  uVar1 = *(undefined1 *)(param_1 + 0x1a);
  param_2[1] = 0;
  param_2[2] = 0;
  *param_2 = uVar1;
  param_2[3] = 0;
  param_2[4] = 0;
  param_2[5] = 0;
  return 0x16;
}

