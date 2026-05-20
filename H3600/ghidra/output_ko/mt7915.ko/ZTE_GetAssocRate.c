// module: mt7915.ko
// function: ZTE_GetAssocRate @ 0x157b48
// size: 232 bytes
//

void ZTE_GetAssocRate(int param_1,uint *param_2)

{
  ushort uVar1;
  uint uVar2;
  uint local_14;
  
  *param_2 = 0;
  local_14 = 0;
  if (*(int *)(param_1 + 8) != 0) {
    HcGetBandByWdev(*(int *)(param_1 + 8));
    uVar1 = *(ushort *)(param_1 + 0xbe);
    uVar2 = (uint)uVar1;
    if (uVar2 < 0xa000) {
      getRate(uVar2,&local_14);
      *param_2 = local_14 & 0xffff;
    }
    else {
      get_rate_he(*(byte *)(param_1 + 0xb7d) & 0xf,(uVar2 << 0x17) >> 0x1e,
                  ((uVar2 << 0x1a) >> 0x1e) + 1,((uint)*(byte *)(param_1 + 0xb7d) << 0x1b) >> 0x1f,
                  &local_14);
      *param_2 = local_14 & 0xffff;
    }
    if (((uVar2 & 0xffffe180) == 0x8000) && ((uVar2 & 0xf) == 9)) {
      uVar2 = (uVar2 & 0x3f) >> 4;
      if (uVar2 == 0) {
        if ((uVar1 & 0x200) == 0) {
          uVar2 = 0x56;
        }
        else {
          uVar2 = 0x60;
        }
        *param_2 = uVar2;
      }
      else if (uVar2 == 1) {
        if ((uVar1 & 0x200) == 0) {
          uVar2 = 0xad;
        }
        else {
          uVar2 = 0xc0;
        }
        *param_2 = uVar2;
      }
    }
  }
  return;
}

