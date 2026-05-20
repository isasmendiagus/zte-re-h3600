// module: mt7915.ko
// function: rtinet_aton @ 0xeeac0
// size: 440 bytes
//

undefined4 rtinet_aton(byte *param_1,uint *param_2)

{
  byte bVar1;
  byte *pbVar2;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  uint *puVar6;
  int iVar7;
  uint uVar8;
  bool bVar9;
  uint local_30 [5];
  
  local_30[0] = 0;
  local_30[1] = 0;
  local_30[2] = 0;
  uVar3 = (uint)*param_1;
  puVar5 = local_30;
  if (uVar3 != 0x30) {
    iVar7 = 10;
    puVar5 = local_30;
    goto LAB_000eeb00;
  }
LAB_000eeb8c:
  uVar3 = (uint)param_1[1];
  if ((uVar3 & 0xffffffdf) == 0x58) {
    uVar3 = (uint)param_1[2];
    iVar7 = 0x10;
    param_1 = param_1 + 2;
  }
  else {
    param_1 = param_1 + 1;
    iVar7 = 8;
  }
LAB_000eeb00:
  uVar8 = 0;
  pbVar2 = param_1;
  do {
    param_1 = pbVar2 + 1;
    if (uVar3 == 0) goto LAB_000eebd4;
    bVar1 = (&_ctype)[uVar3];
    if ((bVar1 & 4) == 0) {
      if ((iVar7 != 0x10) || ((bVar1 & 0x44) == 0)) break;
      if ((bVar1 & 2) == 0) {
        iVar4 = 0x41;
      }
      else {
        iVar4 = 0x61;
      }
      uVar8 = (((char)uVar3 + 10) - iVar4) + uVar8 * 0x10;
    }
    else {
      uVar8 = (iVar7 * uVar8 + (int)(char)uVar3) - 0x30;
    }
    uVar3 = (uint)*param_1;
    pbVar2 = param_1;
  } while( true );
  if (uVar3 != 0x2e) {
LAB_000eebd4:
    while( true ) {
      if (uVar3 == 0) {
        iVar7 = (int)puVar5 - (int)local_30 >> 2;
        if (iVar7 == 2) {
          if (0xffff < uVar8) {
            return 0;
          }
          uVar8 = local_30[0] << 0x18 | local_30[1] << 0x10 | uVar8;
        }
        else if (iVar7 == 3) {
          if (0xff < uVar8) {
            return 0;
          }
          uVar8 = local_30[0] << 0x18 | local_30[1] << 0x10 | local_30[2] << 8 | uVar8;
        }
        else if (iVar7 == 1) {
          if (0xffffff < uVar8) {
            return 0;
          }
          uVar8 = uVar8 | local_30[0] << 0x18;
        }
        *param_2 = uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 |
                   uVar8 >> 0x18;
        return 1;
      }
      if (((&_ctype)[uVar3] & 0x20) == 0) break;
      pbVar2 = pbVar2 + 1;
      uVar3 = (uint)*pbVar2;
    }
    return 0;
  }
  bVar9 = 0xfe < uVar8;
  if (uVar8 < 0x100) {
    bVar9 = local_30 + 3 <= puVar5;
  }
  if (bVar9) {
    return 0;
  }
  uVar3 = (uint)*param_1;
  puVar6 = puVar5 + 1;
  *puVar5 = uVar8;
  puVar5 = puVar6;
  if (uVar3 == 0x30) goto LAB_000eeb8c;
  iVar7 = 10;
  goto LAB_000eeb00;
}

