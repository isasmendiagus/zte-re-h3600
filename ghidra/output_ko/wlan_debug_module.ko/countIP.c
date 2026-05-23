// module: wlan_debug_module.ko
// function: countIP @ 0x117b0
// size: 732 bytes
//

void countIP(int param_1,int param_2,undefined4 param_3,undefined4 *param_4,undefined4 *param_5,
            int param_6,uint param_7,undefined4 param_8)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  ushort uVar7;
  undefined *__s2;
  ushort uVar8;
  uint uVar9;
  int iVar10;
  
  uVar3 = *(byte *)(param_1 + 0xe) & 0xf;
  uVar1 = *(ushort *)(param_1 + 0x10) << 8 | *(ushort *)(param_1 + 0x10) >> 8;
  uVar4 = uVar3 * 4;
  if (uVar3 == 5) {
    uVar7 = *(ushort *)(param_1 + 0x22);
    iVar5 = 0x24;
  }
  else {
    if (0x14 < uVar4) {
      uVar4 = uVar4 + 0xe;
    }
    uVar7 = *(ushort *)(param_1 + uVar4);
    iVar5 = uVar4 + 2;
  }
  uVar8 = uVar7 << 8 | uVar7 >> 8;
  iVar10 = param_2 * 0xfa6 + param_6;
  iVar2 = *(int *)(param_1 + 0x1a);
  uVar7 = *(ushort *)(param_1 + iVar5) << 8 | *(ushort *)(param_1 + iVar5) >> 8;
  iVar6 = iVar10 + 0xfa4;
  iVar5 = *(int *)(param_1 + 0x1e);
  uVar3 = *(uint *)(&g_pktlist + (iVar10 + 0xfa2) * 4);
  *(int *)(&g_pktlist + iVar6 * 4) = *(int *)(&g_pktlist + iVar6 * 4) + 1;
  uVar4 = uVar3;
  if (uVar3 != 0) {
    uVar9 = 0;
    __s2 = &DAT_00017d38 + param_2 * 0x3e98 + param_6 * 8000;
    do {
      if ((((iVar2 == *(int *)(__s2 + -0x30)) && (*(int *)(__s2 + -0x20) == iVar5)) &&
          (*(ushort *)(__s2 + -10) == uVar8)) &&
         (((*(ushort *)(__s2 + -8) == uVar7 && (iVar6 = memcmp(param_4,__s2 + -6,6), iVar6 == 0)) &&
          (iVar6 = memcmp(param_5,__s2,6), iVar6 == 0)))) {
        iVar6 = param_2 * 0x3e98 + param_6 * 8000 + uVar9 * 0x50;
        uVar4 = *(uint *)(&DAT_00017d48 + iVar6);
        *(uint *)(&DAT_00017d48 + iVar6) = uVar4 + param_7;
        *(uint *)(&DAT_00017d4c + iVar6) =
             *(int *)(&DAT_00017d4c + iVar6) + (uint)CARRY4(uVar4,param_7);
        uVar4 = *(uint *)(&DAT_00017d50 + iVar6);
        *(int *)(&DAT_00017d40 + iVar6) = *(int *)(&DAT_00017d40 + iVar6) + 1;
        *(uint *)(&DAT_00017d50 + iVar6) = uVar4 + uVar1;
        *(uint *)(&DAT_00017d54 + iVar6) =
             *(int *)(&DAT_00017d54 + iVar6) + (uint)CARRY4(uVar4,(uint)uVar1);
        uVar4 = uVar9;
        if (uVar9 < uVar3) {
          return;
        }
        break;
      }
      uVar9 = uVar9 + 1;
      __s2 = __s2 + 0x50;
    } while (uVar9 != uVar3);
  }
  if (99 < uVar3) {
    return;
  }
  iVar6 = param_2 * 0x3e98 + param_6 * 8000 + uVar4 * 0x50;
  iVar10 = param_2 * 0xfa6 + param_6 + 0xfa2;
  *(int *)(&DAT_00017d08 + iVar6) = iVar2;
  *(ushort *)(&DAT_00017d30 + iVar6) = uVar7;
  *(ushort *)(&DAT_00017d2e + iVar6) = uVar8;
  *(int *)(&DAT_00017d18 + iVar6) = iVar5;
  *(undefined4 *)(&DAT_00017d32 + iVar6) = *param_4;
  *(undefined2 *)(&DAT_00017d36 + iVar6) = *(undefined2 *)(param_4 + 1);
  *(undefined4 *)(&DAT_00017d38 + iVar6) = *param_5;
  *(undefined2 *)(&DAT_00017d3c + iVar6) = *(undefined2 *)(param_5 + 1);
  *(uint *)(&DAT_00017d48 + iVar6) = param_7;
  iVar5 = *(int *)(&g_pktlist + iVar10 * 4);
  *(uint *)(&DAT_00017d50 + iVar6) = (uint)uVar1;
  *(undefined4 *)(&DAT_00017d54 + iVar6) = 0;
  *(undefined4 *)(&DAT_00017d28 + iVar6) = param_8;
  (&DAT_00017d2c)[iVar6] = 1;
  *(undefined4 *)(&DAT_00017d40 + iVar6) = 1;
  *(undefined4 *)(&DAT_00017d4c + iVar6) = 0;
  *(int *)(&g_pktlist + iVar10 * 4) = iVar5 + 1;
  return;
}

