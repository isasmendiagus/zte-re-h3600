// module: mt7915.ko
// function: getRate @ 0xe358c
// size: 420 bytes
//

void getRate(uint param_1,int *param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint in_r12;
  int iVar4;
  uint uVar5;
  int iVar6;
  bool bVar7;
  
  uVar3 = (param_1 << 0x10) >> 0x1d;
  uVar5 = param_1 & 0x3f;
  iVar6 = (int)(param_1 << 0x16) >> 0x1f;
  if (uVar3 < 4) {
    if (uVar3 < 2) {
      uVar2 = (param_1 << 0x10) >> 0x18 & 0xe0;
      if (uVar2 == 0x20) {
        uVar5 = uVar5 + 4;
        iVar4 = 0;
      }
      else {
        if (uVar2 != 0) {
          uVar5 = 0;
        }
        iVar4 = 0;
      }
    }
    else {
      bVar7 = ((param_1 << 0x10) >> 0x18 & 0xc0) == 0x40;
      if (bVar7) {
        in_r12 = uVar5 >> 3;
      }
      if (bVar7) {
        iVar4 = in_r12 + 1;
      }
      else {
        iVar4 = 0;
      }
      if (7 < uVar5) {
        uVar5 = param_1 & 7;
      }
      uVar5 = ((param_1 << 0x17) >> 0x1e) * 0x18 + 0x10 + iVar6 * -0x30 + uVar5;
    }
    iVar6 = (*(int *)(MCSMappingRateTable + uVar5 * 4) * 5) / 10;
  }
  else {
    uVar2 = param_1 & 0x180;
    iVar1 = (int)uVar5 >> 4;
    iVar4 = iVar1 + 1;
    param_1 = param_1 & 0xf;
    if (uVar2 == 0) {
      iVar6 = iVar1 * 10 + 0x70 + iVar6 * -0xa0 + param_1;
    }
    else if (uVar2 == 0x80) {
      iVar6 = iVar1 * 10 + 0x98 + iVar6 * -0xa0 + param_1;
    }
    else if (uVar2 == 0x100) {
      iVar6 = iVar1 * 10 + 0xc0 + iVar6 * -0xa0 + param_1;
    }
    else if (uVar2 == 0x180) {
      iVar6 = iVar1 * 10 + 0xe8 + iVar6 * -0xa0 + param_1;
    }
    else {
      iVar6 = 0;
    }
    iVar6 = *(int *)(MCSMappingRateTable + iVar6 * 4);
  }
  if ((uVar3 + 6 & 7) < 2) {
    iVar6 = iVar4 * iVar6;
  }
  *param_2 = iVar6;
  return;
}

