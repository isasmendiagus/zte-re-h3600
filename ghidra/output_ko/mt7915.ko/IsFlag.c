// module: mt7915.ko
// function: IsFlag @ 0x16d040
// size: 72 bytes
//

undefined4 IsFlag(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_1 < 2) {
    return 0;
  }
  if (DebugLevel < 0) {
    return 1;
  }
  printk("ArgNum[%d] = %d is invalid Value! (ArgVal !=0 && ArgVal !=1)\n",param_2,param_1,DebugLevel
         ,param_4);
  return 1;
}

