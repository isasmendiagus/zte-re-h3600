// module: mt7915.ko
// function: getViewLevelValue @ 0x1559e8
// size: 40 bytes
//

undefined4 getViewLevelValue(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 != 0) {
    _LANCHOR1 = &_LANCHOR2;
    uVar1 = FUN_00153d9c();
    return uVar1;
  }
  return 0xffffffff;
}

