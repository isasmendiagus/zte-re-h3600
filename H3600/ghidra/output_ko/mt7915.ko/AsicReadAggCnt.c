// module: mt7915.ko
// function: AsicReadAggCnt @ 0x133e44
// size: 48 bytes
//

undefined4 AsicReadAggCnt(undefined4 param_1,undefined4 param_2,int param_3)

{
  if (param_3 << 2 != 0) {
    __memzero(param_2,param_3 << 2);
  }
  AsicNotSupportFunc(param_1,"AsicReadAggCnt");
  return 0;
}

