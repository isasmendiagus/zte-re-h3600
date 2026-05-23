// module: mt7915.ko
// function: mt_clientSupportsVhtETxBF @ 0x854c0
// size: 24 bytes
//

uint mt_clientSupportsVhtETxBF(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  if ((*(byte *)(param_2 + 1) & 0x10) == 0) {
    uVar1 = ((uint)*(byte *)(param_2 + 2) << 0x1b) >> 0x1f;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

