// module: mt7915.ko
// function: RcGetHdevByChannel @ 0xac654
// size: 128 bytes
//

int RcGetHdevByChannel(int param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  if (*(byte *)(param_1 + 0x32d8) != 0) {
    if (*(byte *)(*(int *)(param_1 + 4) + 4) == param_2) {
      return param_1;
    }
    if ((1 < *(byte *)(param_1 + 0x32d8)) && (*(byte *)(*(int *)(param_1 + 0x20) + 4) == param_2)) {
      return param_1 + 0x1c;
    }
  }
  if (DebugLevel < 4) {
    return 0;
  }
  printk("%s():Err! Update PhyMode failed, no phyctrl support this channel=%d!\n",
         "RcGetHdevByChannel",param_2,DebugLevel,param_4);
  return 0;
}

