// module: mt7915.ko
// function: RTMP_STA_IoctlPrepare @ 0x150078
// size: 180 bytes
//

undefined4 RTMP_STA_IoctlPrepare(int *param_1,int *param_2)

{
  char *__s2;
  int iVar1;
  int iVar2;
  char *__s1;
  
  iVar1 = param_2[2];
  iVar2 = *param_1;
  if (iVar1 == 0x100) {
    iVar1 = 0;
    *(undefined4 *)(iVar2 + 0x38) = 0x100;
    *(undefined4 *)(iVar2 + 0x3c) = 0;
  }
  else if (iVar1 == 0x800) {
    *(undefined4 *)(iVar2 + 0x38) = 0x800;
    __s1 = (char *)param_2[3];
    __s2 = (char *)RtmpOsGetNetDevName(param_1[1]);
    iVar1 = strcmp(__s1,__s2);
    if (iVar1 == 0) {
      *(undefined4 *)(iVar2 + 0x3c) = 0;
      iVar1 = 0;
    }
    else {
      if (param_1[0x1604c2] != *param_2) {
        return 0xffffff9c;
      }
      iVar1 = 1;
      *(undefined4 *)(iVar2 + 0x3c) = 1;
    }
  }
  else {
    if (iVar1 != 0x400) {
      return 0xffffffa1;
    }
    *(undefined4 *)(iVar2 + 0x38) = 0x400;
    iVar1 = 0;
    *(undefined4 *)(iVar2 + 0x3c) = 0;
  }
  param_2[4] = iVar1;
  return 0;
}

