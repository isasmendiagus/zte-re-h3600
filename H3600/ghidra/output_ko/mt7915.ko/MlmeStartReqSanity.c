// module: mt7915.ko
// function: MlmeStartReqSanity @ 0x52974
// size: 96 bytes
//

undefined4
MlmeStartReqSanity(undefined4 param_1,void *param_2,undefined4 param_3,void *param_4,byte *param_5)

{
  uint __n;
  
  __n = (uint)*(byte *)((int)param_2 + 0x20);
  if (__n < 0x21) {
    *param_5 = *(byte *)((int)param_2 + 0x20);
    memmove(param_4,param_2,__n);
    return 1;
  }
  if (DebugLevel < 3) {
    return 0;
  }
  printk("%s(): fail - wrong SSID length\n","MlmeStartReqSanity",__n,DebugLevel,param_4);
  return 0;
}

