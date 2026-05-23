// module: mt7915.ko
// function: rtmp_read_wsc_user_parms @ 0xf0464
// size: 572 bytes
//

void rtmp_read_wsc_user_parms(int param_1,char *param_2,undefined4 param_3)

{
  int iVar1;
  size_t sVar2;
  
  iVar1 = RTMPGetKeyParameter("WscManufacturer",param_2,0x40,param_3,1);
  if (iVar1 != 0) {
    __memzero((void *)(param_1 + 0xcb),0x40);
    sVar2 = strlen(param_2);
    memmove((void *)(param_1 + 0xcb),param_2,sVar2);
    if (*(char *)(param_1 + 0xcb) != '\0') {
      *(byte *)(param_1 + 0x2a5a) = *(byte *)(param_1 + 0x2a5a) | 1;
    }
  }
  iVar1 = RTMPGetKeyParameter("WscModelName",param_2,0x20,param_3,1);
  if (iVar1 != 0) {
    __memzero((void *)(param_1 + 0x10b),0x20);
    sVar2 = strlen(param_2);
    memmove((void *)(param_1 + 0x10b),param_2,sVar2);
    if (*(char *)(param_1 + 0x10b) != '\0') {
      *(byte *)(param_1 + 0x2a5a) = *(byte *)(param_1 + 0x2a5a) | 2;
    }
  }
  iVar1 = RTMPGetKeyParameter("WscDeviceName",param_2,0x20,param_3,1);
  if (iVar1 != 0) {
    __memzero((void *)(param_1 + 0x88),0x20);
    sVar2 = strlen(param_2);
    memmove((void *)(param_1 + 0x88),param_2,sVar2);
    if (*(char *)(param_1 + 0x88) != '\0') {
      *(byte *)(param_1 + 0x2a5a) = *(byte *)(param_1 + 0x2a5a) | 4;
    }
  }
  iVar1 = RTMPGetKeyParameter("WscModelNumber",param_2,0x20,param_3,1);
  if (iVar1 != 0) {
    __memzero((void *)(param_1 + 299),0x20);
    sVar2 = strlen(param_2);
    memmove((void *)(param_1 + 299),param_2,sVar2);
    if (*(char *)(param_1 + 299) != '\0') {
      *(byte *)(param_1 + 0x2a5a) = *(byte *)(param_1 + 0x2a5a) | 8;
    }
  }
  iVar1 = RTMPGetKeyParameter("WscSerialNumber",param_2,0x20,param_3,1);
  if (iVar1 != 0) {
    __memzero((void *)(param_1 + 0x14b),0x20);
    sVar2 = strlen(param_2);
    memmove((void *)(param_1 + 0x14b),param_2,sVar2);
    if (*(char *)(param_1 + 0x14b) != '\0') {
      *(byte *)(param_1 + 0x2a5a) = *(byte *)(param_1 + 0x2a5a) | 0x10;
    }
  }
  return;
}

