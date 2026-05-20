// module: mt7915.ko
// function: SecAuthModeOldToNew @ 0x1135f8
// size: 28 bytes
//

undefined4 SecAuthModeOldToNew(uint param_1)

{
  undefined4 uVar1;
  
  if (param_1 < 10) {
    uVar1 = (&DAT_00297998)[param_1];
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

