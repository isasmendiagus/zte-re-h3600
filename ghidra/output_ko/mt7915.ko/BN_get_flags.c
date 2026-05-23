// module: mt7915.ko
// function: BN_get_flags @ 0x20e188
// size: 16 bytes
//

uint BN_get_flags(int param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = 0;
  if (param_1 != 0) {
    uVar1 = param_2 & *(uint *)(param_1 + 0x10);
  }
  return uVar1;
}

