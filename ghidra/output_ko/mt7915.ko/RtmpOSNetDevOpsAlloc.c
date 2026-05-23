// module: mt7915.ko
// function: RtmpOSNetDevOpsAlloc @ 0x244218
// size: 52 bytes
//

undefined4 RtmpOSNetDevOpsAlloc(int *param_1)

{
  int iVar1;
  
  iVar1 = vmalloc(0xdc);
  *param_1 = iVar1;
  if (iVar1 != 0) {
    __memzero(iVar1,0xdc);
    return 0;
  }
  return 1;
}

