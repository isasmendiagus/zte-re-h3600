// module: mt7915.ko
// function: RtmpOSNetDevAddrSet @ 0x24411c
// size: 100 bytes
//

undefined4 RtmpOSNetDevAddrSet(int param_1,char *param_2,void *param_3,void *param_4)

{
  size_t __n;
  
  if (param_4 != (void *)0x0 && param_1 == 0) {
    __memzero(param_4,0x10);
    __n = strlen(param_2);
    memmove(param_4,param_2,__n);
  }
  memmove(*(void **)(param_2 + 0x1dc),param_3,6);
  return 0;
}

