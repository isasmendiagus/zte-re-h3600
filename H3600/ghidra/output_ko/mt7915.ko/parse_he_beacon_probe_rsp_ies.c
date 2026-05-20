// module: mt7915.ko
// function: parse_he_beacon_probe_rsp_ies @ 0x205534
// size: 216 bytes
//

uint parse_he_beacon_probe_rsp_ies(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  uint __n;
  void *pvVar3;
  
  pvVar3 = (void *)(param_1 + 3);
  iVar2 = *(byte *)(param_1 + 2) - 0x23;
  __n = *(byte *)(param_1 + 1) - 1 & 0xff;
  switch(iVar2) {
  case 0:
    if (0x14 < __n) {
      *(uint *)(param_2 + 0xa8) = *(uint *)(param_2 + 0xa8) | 0x10;
      memmove((void *)(param_2 + 0x122),pvVar3,0x15);
      pvVar3 = (void *)(param_1 + 0x18);
      uVar1 = (uint)(*(int *)(param_2 + 0x128) << 0x18) >> 0x19;
      if ((uVar1 & 2) != 0) {
        if ((uVar1 & 4) == 0) {
          if ((uVar1 & 8) != 0) {
            memmove((void *)(param_2 + 0x13b),pvVar3,4);
          }
        }
        else if ((uVar1 & 8) == 0) {
          memmove((void *)(param_2 + 0x137),pvVar3,4);
        }
        else {
          memmove((void *)(param_2 + 0x13b),pvVar3,4);
        }
      }
      return __n;
    }
    break;
  case 1:
    if (5 < __n) {
      *(uint *)(param_2 + 0xa8) = *(uint *)(param_2 + 0xa8) | 0x20;
      memmove((void *)(param_2 + 0x13f),pvVar3,6);
      if ((*(ushort *)(param_2 + 0x13f) & 0x4000) != 0) {
        memmove((void *)(param_2 + 0x168),(void *)(param_1 + 9),3);
        return __n;
      }
      return __n;
    }
    break;
  case 3:
    __memzero((void *)(param_2 + 0x16b),0xd,param_3,iVar2,param_4);
    if (0xc < __n) {
      *(uint *)(param_2 + 0xa8) = *(uint *)(param_2 + 0xa8) | 0x100;
      memmove((void *)(param_2 + 0x16b),pvVar3,__n);
      return __n;
    }
    break;
  case 4:
    __memzero((void *)(param_2 + 0x148),0x20,param_3,iVar2,param_4);
    if (__n != 0) {
      memmove((void *)(param_2 + 0x148),pvVar3,__n);
      return __n;
    }
  }
  return 0;
}

