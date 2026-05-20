// module: mt7915.ko
// function: multi_profile_get_pf1_num @ 0x166d1c
// size: 24 bytes
//

undefined1 multi_profile_get_pf1_num(int param_1)

{
  undefined1 uVar1;
  
  uVar1 = 0;
  if (*(int *)(param_1 + 0xa7cbdc) != 0) {
    uVar1 = *(undefined1 *)(*(int *)(param_1 + 0xa7cbdc) + 2);
  }
  return uVar1;
}

