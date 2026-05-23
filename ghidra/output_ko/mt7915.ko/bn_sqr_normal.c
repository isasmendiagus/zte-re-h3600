// module: mt7915.ko
// function: bn_sqr_normal @ 0x20f308
// size: 452 bytes
//

void bn_sqr_normal(undefined4 *param_1,uint *param_2,int param_3,uint *param_4)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 *puVar9;
  uint *unaff_r10;
  uint uVar10;
  
  iVar8 = param_3 + -1;
  iVar1 = param_3 * 2;
  param_1[iVar1 + 0x3fffffff] = 0;
  if (iVar8 < 1) {
    unaff_r10 = param_2;
  }
  puVar9 = param_1 + 1;
  *param_1 = 0;
  if (0 < iVar8) {
    unaff_r10 = param_2 + 1;
    uVar3 = FUN_0020cb1c(puVar9,unaff_r10,iVar8,*param_2);
    puVar9[iVar8] = uVar3;
    puVar9 = param_1 + 3;
  }
  iVar8 = param_3 + -2;
  if (0 < iVar8) {
    puVar7 = puVar9 + param_3 + 0x3ffffffd;
    do {
      uVar3 = FUN_0020c980(puVar9,unaff_r10 + 1,iVar8,*unaff_r10);
      iVar8 = iVar8 + -1;
      puVar7 = puVar7 + 1;
      *puVar7 = uVar3;
      puVar9 = puVar9 + 2;
      unaff_r10 = unaff_r10 + 1;
    } while (iVar8 != 0);
  }
  FUN_0020cc88(param_1,param_1,param_1,iVar1);
  puVar6 = param_4;
  if (0 < param_3) {
    do {
      uVar4 = *param_2 & 0xffff;
      uVar10 = *param_2 >> 0x10;
      uVar2 = uVar4 * uVar10 * 0x20000;
      uVar5 = uVar4 * uVar4 + uVar2;
      uVar10 = uVar10 * uVar10 + (uVar4 * uVar10 >> 0xf);
      if (uVar5 <= uVar2 && uVar2 - uVar5 != 0) {
        uVar10 = uVar10 + 1;
      }
      *puVar6 = uVar5;
      puVar6[1] = uVar10;
      if (param_3 == 1) break;
      uVar4 = param_2[1] & 0xffff;
      uVar10 = param_2[1] >> 0x10;
      uVar2 = uVar4 * uVar10 * 0x20000;
      uVar5 = uVar4 * uVar4 + uVar2;
      uVar10 = uVar10 * uVar10 + (uVar4 * uVar10 >> 0xf);
      if (uVar5 <= uVar2 && uVar2 - uVar5 != 0) {
        uVar10 = uVar10 + 1;
      }
      puVar6[2] = uVar5;
      puVar6[3] = uVar10;
      if (param_3 == 2) break;
      uVar4 = param_2[2] & 0xffff;
      uVar10 = param_2[2] >> 0x10;
      uVar2 = uVar4 * uVar10 * 0x20000;
      uVar5 = uVar4 * uVar4 + uVar2;
      uVar10 = uVar10 * uVar10 + (uVar4 * uVar10 >> 0xf);
      if (uVar5 <= uVar2 && uVar2 - uVar5 != 0) {
        uVar10 = uVar10 + 1;
      }
      puVar6[4] = uVar5;
      puVar6[5] = uVar10;
      if (param_3 == 3) break;
      uVar4 = param_2[3] & 0xffff;
      uVar10 = param_2[3] >> 0x10;
      uVar2 = uVar4 * uVar10 * 0x20000;
      uVar5 = uVar4 * uVar4 + uVar2;
      uVar10 = uVar10 * uVar10 + (uVar4 * uVar10 >> 0xf);
      if (uVar5 <= uVar2 && uVar2 - uVar5 != 0) {
        uVar10 = uVar10 + 1;
      }
      param_3 = param_3 + -4;
      puVar6[7] = uVar10;
      puVar6[6] = uVar5;
      param_2 = param_2 + 4;
      puVar6 = puVar6 + 8;
    } while (param_3 != 0);
  }
  FUN_0020cc88(param_1,param_1,param_4,iVar1);
  return;
}

