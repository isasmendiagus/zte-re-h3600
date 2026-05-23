// module: mt7915.ko
// function: is_multi_profile_enable @ 0x166d04
// size: 24 bytes
//

undefined1 is_multi_profile_enable(int param_1)

{
  undefined1 uVar1;
  
  uVar1 = 0;
  if (*(undefined1 **)(param_1 + 0xa7cbdc) != (undefined1 *)0x0) {
    uVar1 = **(undefined1 **)(param_1 + 0xa7cbdc);
  }
  return uVar1;
}

