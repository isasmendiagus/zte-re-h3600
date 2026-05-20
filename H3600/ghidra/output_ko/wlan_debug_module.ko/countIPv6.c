// module: wlan_debug_module.ko
// function: countIPv6 @ 0x11a8c
// size: 936 bytes
//

void countIPv6(int param_1,int param_2,undefined4 param_3,undefined4 *param_4,undefined4 *param_5,
              int param_6,uint param_7,undefined4 param_8)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  ushort uVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  undefined *__s2;
  uint uVar13;
  uint uVar14;
  ushort uVar15;
  
  iVar2 = *(int *)(param_1 + 0x16);
  iVar3 = *(int *)(param_1 + 0x1a);
  iVar10 = param_2 * 0xfa6 + param_6;
  iVar4 = *(int *)(param_1 + 0x1e);
  uVar9 = *(ushort *)(param_1 + 0x36) << 8 | *(ushort *)(param_1 + 0x36) >> 8;
  iVar5 = *(int *)(param_1 + 0x22);
  iVar12 = iVar10 + 0xfa4;
  uVar14 = *(uint *)(&g_pktlist + (iVar10 + 0xfa2) * 4);
  uVar15 = *(ushort *)(param_1 + 0x38) << 8 | *(ushort *)(param_1 + 0x38) >> 8;
  iVar10 = *(int *)(param_1 + 0x26);
  iVar6 = *(int *)(param_1 + 0x2a);
  uVar1 = *(ushort *)(param_1 + 0x12) << 8 | *(ushort *)(param_1 + 0x12) >> 8;
  iVar7 = *(int *)(param_1 + 0x2e);
  iVar8 = *(int *)(param_1 + 0x32);
  *(int *)(&g_pktlist + iVar12 * 4) = *(int *)(&g_pktlist + iVar12 * 4) + 1;
  uVar11 = uVar14;
  if (uVar14 != 0) {
    uVar13 = 0;
    __s2 = &DAT_00017d38 + param_2 * 0x3e98 + param_6 * 8000;
    do {
      if (((((*(int *)(__s2 + -0x30) == iVar2) && (*(int *)(__s2 + -0x2c) == iVar3)) &&
           (*(int *)(__s2 + -0x28) == iVar4)) &&
          ((((*(int *)(__s2 + -0x24) == iVar5 && (*(int *)(__s2 + -0x20) == iVar10)) &&
            ((*(int *)(__s2 + -0x1c) == iVar6 &&
             ((*(int *)(__s2 + -0x18) == iVar7 && (*(int *)(__s2 + -0x14) == iVar8)))))) &&
           (*(ushort *)(__s2 + -10) == uVar9)))) &&
         (((*(ushort *)(__s2 + -8) == uVar15 && (iVar12 = memcmp(param_4,__s2 + -6,6), iVar12 == 0))
          && (iVar12 = memcmp(param_5,__s2,6), iVar12 == 0)))) {
        iVar12 = param_2 * 0x3e98 + param_6 * 8000 + uVar13 * 0x50;
        uVar11 = *(uint *)(&DAT_00017d48 + iVar12);
        *(uint *)(&DAT_00017d48 + iVar12) = uVar11 + param_7;
        *(uint *)(&DAT_00017d4c + iVar12) =
             *(int *)(&DAT_00017d4c + iVar12) + (uint)CARRY4(uVar11,param_7);
        uVar11 = *(uint *)(&DAT_00017d50 + iVar12);
        *(int *)(&DAT_00017d40 + iVar12) = *(int *)(&DAT_00017d40 + iVar12) + 1;
        *(uint *)(&DAT_00017d50 + iVar12) = uVar11 + uVar1;
        *(uint *)(&DAT_00017d54 + iVar12) =
             *(int *)(&DAT_00017d54 + iVar12) + (uint)CARRY4(uVar11,(uint)uVar1);
        uVar11 = uVar13;
        if (uVar13 < uVar14) {
          return;
        }
        break;
      }
      uVar13 = uVar13 + 1;
      __s2 = __s2 + 0x50;
    } while (uVar13 != uVar14);
  }
  if (99 < uVar14) {
    return;
  }
  iVar12 = param_2 * 0x3e98 + param_6 * 8000 + uVar11 * 0x50;
  *(ushort *)(&DAT_00017d30 + iVar12) = uVar15;
  *(int *)(&DAT_00017d14 + iVar12) = iVar5;
  iVar5 = param_2 * 0xfa6 + param_6 + 0xfa2;
  *(int *)(&DAT_00017d08 + iVar12) = iVar2;
  *(int *)(&DAT_00017d0c + iVar12) = iVar3;
  *(int *)(&DAT_00017d10 + iVar12) = iVar4;
  *(int *)(&DAT_00017d18 + iVar12) = iVar10;
  *(int *)(&DAT_00017d20 + iVar12) = iVar7;
  *(ushort *)(&DAT_00017d2e + iVar12) = uVar9;
  *(int *)(&DAT_00017d1c + iVar12) = iVar6;
  *(int *)(&DAT_00017d24 + iVar12) = iVar8;
  *(undefined4 *)(&DAT_00017d32 + iVar12) = *param_4;
  *(undefined2 *)(&DAT_00017d36 + iVar12) = *(undefined2 *)(param_4 + 1);
  *(undefined4 *)(&DAT_00017d38 + iVar12) = *param_5;
  *(undefined2 *)(&DAT_00017d3c + iVar12) = *(undefined2 *)(param_5 + 1);
  iVar2 = *(int *)(&g_pktlist + iVar5 * 4);
  *(uint *)(&DAT_00017d48 + iVar12) = param_7;
  *(undefined4 *)(&DAT_00017d40 + iVar12) = 1;
  (&DAT_00017d2c)[iVar12] = 0;
  *(undefined4 *)(&DAT_00017d28 + iVar12) = param_8;
  *(uint *)(&DAT_00017d50 + iVar12) = (uint)uVar1;
  *(undefined4 *)(&DAT_00017d54 + iVar12) = 0;
  *(undefined4 *)(&DAT_00017d4c + iVar12) = 0;
  *(int *)(&g_pktlist + iVar5 * 4) = iVar2 + 1;
  return;
}

