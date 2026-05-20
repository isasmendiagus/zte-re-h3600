// module: mt7915.ko
// function: IsInRange @ 0x16d088
// size: 40 bytes
//

undefined4 IsInRange(int param_1,undefined4 param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  
  if (param_1 <= param_4 && param_3 <= param_1) {
    return 0;
  }
  uVar1 = FUN_0016b374();
  return uVar1;
}

