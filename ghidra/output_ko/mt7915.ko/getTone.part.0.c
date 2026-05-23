// module: mt7915.ko
// function: getTone.part.0 @ 0x28f3c0
// size: 40 bytes
//

undefined4 getTone_part_0(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 - 7U < 8) {
    return 2;
  }
  if (param_1 - 0xfU < 8) {
    uVar1 = 3;
  }
  else {
    uVar1 = 4;
  }
  return uVar1;
}

