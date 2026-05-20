// module: mt7915.ko
// function: parse_he_assoc_rsp_ies @ 0x205af0
// size: 340 bytes
//

uint parse_he_assoc_rsp_ies(int param_1,int param_2)

{
  uint uVar1;
  uint __n;
  void *pvVar2;
  
  pvVar2 = (void *)(param_1 + 3);
  __n = *(byte *)(param_1 + 1) - 1 & 0xff;
  switch(*(undefined1 *)(param_1 + 2)) {
  case 0x23:
    if (0x14 < __n) {
      *(uint *)(param_2 + 0x240) = *(uint *)(param_2 + 0x240) | 0x10;
      memmove((void *)(param_2 + 0x2ba),pvVar2,0x15);
      pvVar2 = (void *)(param_1 + 0x18);
      uVar1 = (uint)(*(int *)(param_2 + 0x2c0) << 0x18) >> 0x19;
      if ((uVar1 & 2) != 0) {
        if ((uVar1 & 4) == 0) {
          if ((uVar1 & 8) != 0) {
            memmove((void *)(param_2 + 0x2d3),pvVar2,4);
          }
        }
        else if ((uVar1 & 8) == 0) {
          memmove((void *)(param_2 + 0x2cf),pvVar2,4);
        }
        else {
          memmove((void *)(param_2 + 0x2d3),pvVar2,4);
        }
      }
      return __n;
    }
    break;
  case 0x24:
    if (5 < __n) {
      *(uint *)(param_2 + 0x240) = *(uint *)(param_2 + 0x240) | 0x20;
      memmove((void *)(param_2 + 0x2d7),pvVar2,6);
      if ((*(ushort *)(param_2 + 0x2d7) & 0x4000) == 0) {
        return __n;
      }
      memmove((void *)(param_2 + 0x300),(void *)(param_1 + 9),3);
      return __n;
    }
    break;
  case 0x26:
    __memzero((void *)(param_2 + 0x303),0xd);
    if (__n < 0xd) {
      __n = 0;
    }
    else {
      *(uint *)(param_2 + 0x240) = *(uint *)(param_2 + 0x240) | 0x100;
      memmove((void *)(param_2 + 0x303),pvVar2,__n);
    }
    dump_he_ies("Recv. peer assoc_rsp, mu_edca",param_1,*(undefined1 *)(param_1 + 1));
    return __n;
  case 0x27:
    __memzero((void *)(param_2 + 0x2e0),0x20);
    if (__n != 0) {
      memmove((void *)(param_2 + 0x2e0),pvVar2,__n);
      return __n;
    }
  }
  return 0;
}

