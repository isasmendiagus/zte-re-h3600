// module: mt7915.ko
// function: SecEncryModeOldToNew @ 0x113614
// size: 28 bytes
//

undefined4 SecEncryModeOldToNew(uint param_1)

{
  undefined4 uVar1;
  
  if (param_1 < 0xc) {
    uVar1 = (&DAT_002979c0)[param_1];
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

