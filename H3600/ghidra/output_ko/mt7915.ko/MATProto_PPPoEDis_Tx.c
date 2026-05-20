// module: mt7915.ko
// function: MATProto_PPPoEDis_Tx @ 0x7b674
// size: 1272 bytes
//

int MATProto_PPPoEDis_Tx(int param_1,int param_2,char *param_3)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  char *pcVar4;
  char *pcVar5;
  int iVar6;
  char *pcVar7;
  undefined1 *puVar8;
  uint uVar9;
  ushort uVar10;
  uint uVar11;
  ushort *puVar12;
  undefined1 *puVar14;
  uint uVar15;
  ushort *__src;
  uint __n;
  ushort uVar16;
  char *pcVar17;
  int iVar18;
  ushort *__s1;
  ushort *puVar19;
  ushort *local_48;
  char local_34;
  ushort *puVar13;
  
  puVar19 = *(ushort **)(param_2 + 0xcc);
  if (*param_3 != '\x11') {
    return 0;
  }
  bVar1 = param_3[1];
  if (bVar1 == 9) {
LAB_0007b6e0:
    uVar16 = 0x103;
    bVar3 = false;
LAB_0007b6ec:
    bVar2 = false;
    uVar10 = 0;
  }
  else {
    if (bVar1 < 10) {
      if (bVar1 != 7) {
        return 0;
      }
      uVar16 = 0x104;
      bVar3 = true;
      goto LAB_0007b6ec;
    }
    if (bVar1 == 0x19) goto LAB_0007b6e0;
    if (bVar1 != 0x65) {
      return 0;
    }
    uVar16 = 0x104;
    bVar2 = true;
    uVar10 = *(ushort *)(param_3 + 2) << 8 | *(ushort *)(param_3 + 2) >> 8;
    bVar3 = true;
  }
  local_48 = (ushort *)(param_3 + 6);
  uVar11 = (*(ushort *)(param_3 + 4) & 0xff) << 8 | (uint)(*(ushort *)(param_3 + 4) >> 8);
  uVar9 = uVar11;
  if (uVar11 == 0) {
    __n = 0;
    local_48 = (ushort *)0x0;
  }
  else {
    do {
      __n = (local_48[1] & 0xff) << 8 | (uint)(local_48[1] >> 8);
      uVar9 = uVar9 + (0xfffc - __n) & 0xffff;
      if (uVar16 == (ushort)(*local_48 << 8 | *local_48 >> 8) && __n != 0) {
        local_48 = local_48 + 2;
        goto LAB_0007b77c;
      }
      local_48 = (ushort *)((int)local_48 + __n + 4);
    } while (uVar9 != 0);
    local_48 = (ushort *)0x0;
  }
LAB_0007b77c:
  pcVar5 = *(char **)(param_1 + 0x14);
  __src = puVar19 + 3;
  if ((pcVar5 != (char *)0x0) && (*pcVar5 != '\0')) {
    if (__n == 0 || local_48 == (ushort *)0x0) {
      __n = 6;
      local_34 = '\x01';
      __s1 = __src;
      if (bVar3) {
        __s1 = puVar19;
      }
    }
    else {
      local_34 = '\0';
      __s1 = local_48;
      if (5 < __n) {
        __n = 6;
      }
    }
    uVar9 = 0;
    puVar13 = __s1;
    do {
      puVar12 = (ushort *)((int)puVar13 + 1);
      uVar9 = uVar9 ^ (byte)*puVar13;
      puVar13 = puVar12;
    } while (puVar12 != (ushort *)((int)__s1 + __n));
    uVar9 = uVar9 & 0x3f;
    pcVar4 = *(char **)(pcVar5 + uVar9 * 4 + 4);
    pcVar17 = *(char **)(pcVar5 + uVar9 * 4 + 4);
    iVar18 = jiffies;
    while (pcVar7 = pcVar4, jiffies = iVar18, pcVar7 != (char *)0x0) {
      iVar6 = memcmp(__s1,pcVar7 + 2,__n);
      if ((iVar6 == 0) &&
         (((((*(byte *)((int)puVar19 + 7) == pcVar7[9] && (byte)puVar19[3] == pcVar7[8]) &&
            (byte)puVar19[4] == pcVar7[10]) && *(byte *)((int)puVar19 + 9) == pcVar7[0xb]) &&
          (byte)puVar19[5] == pcVar7[0xc]) && pcVar7[0xd] == *(byte *)((int)puVar19 + 0xb))) {
        *(int *)(pcVar7 + 0x10) = iVar18;
        *pcVar7 = bVar3;
        pcVar7[1] = local_34;
        goto LAB_0007ba24;
      }
      if ((*(int *)(pcVar7 + 0x10) + 30000) - iVar18 < 0) {
        if (pcVar7 == *(char **)(pcVar5 + uVar9 * 4 + 4)) {
          pcVar17 = *(char **)(pcVar7 + 0x14);
          *(char **)(pcVar5 + uVar9 * 4 + 4) = pcVar17;
          MATDBEntryFree(param_1,pcVar7);
          uVar15 = *(int *)(param_1 + 0x1c) - 1;
          *(uint *)(param_1 + 0x1c) = uVar15;
          if (pcVar17 == (char *)0x0) goto LAB_0007b990;
        }
        else {
          *(undefined4 *)(pcVar17 + 0x14) = *(undefined4 *)(pcVar7 + 0x14);
          MATDBEntryFree(param_1,pcVar7);
          *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + -1;
        }
        pcVar4 = *(char **)(pcVar17 + 0x14);
        iVar18 = jiffies;
      }
      else {
        pcVar4 = *(char **)(pcVar7 + 0x14);
        pcVar17 = pcVar7;
        iVar18 = jiffies;
      }
    }
    uVar15 = *(uint *)(param_1 + 0x1c);
LAB_0007b990:
    if ((uVar15 < 0x100) && (pcVar7 = (char *)MATDBEntryAlloc(param_1,0x18), pcVar7 != (char *)0x0))
    {
      __memzero(pcVar7,0x18);
      *pcVar7 = bVar3;
      pcVar7[1] = local_34;
      memmove(pcVar7 + 8,__src,6);
      memmove(pcVar7 + 2,__s1,__n);
      iVar18 = jiffies;
      pcVar7[0x14] = '\0';
      pcVar7[0x15] = '\0';
      pcVar7[0x16] = '\0';
      pcVar7[0x17] = '\0';
      *(int *)(pcVar7 + 0x10) = iVar18;
      if (*(int *)(pcVar5 + uVar9 * 4 + 4) != 0) {
        *(int *)(pcVar7 + 0x14) = *(int *)(pcVar5 + uVar9 * 4 + 4);
      }
      *(char **)(pcVar5 + uVar9 * 4 + 4) = pcVar7;
      *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + 1;
LAB_0007ba24:
      if (local_48 == (ushort *)0x0) {
        if (((*(byte *)(param_2 + 0x72) & 1) != 0) &&
           ((*(uint *)(*(int *)(param_2 + 0xc4) + 0x20) & 0xffff) != 1)) {
          param_2 = skb_copy(param_2,0x20);
          g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
        }
        if (param_2 == 0) {
          return 0;
        }
        puVar8 = (undefined1 *)skb_put(param_2,10);
        if (puVar8 != (undefined1 *)0x0) {
          iVar18 = *(int *)(param_2 + 0xcc);
          puVar14 = (undefined1 *)
                    (iVar18 + ((uint)(param_3 + (4 - (int)puVar19)) & 0xffff) + uVar11);
          if (puVar14 <= puVar8) {
            puVar8 = puVar14;
          }
          if (*pcVar7 == '\0') {
            puVar8[2] = 0;
            puVar8[3] = 6;
            *puVar8 = 1;
            puVar8[1] = 3;
            memmove(puVar8 + 4,pcVar7 + 2,6);
          }
          else {
            puVar8[3] = 6;
            *puVar8 = 1;
            puVar8[1] = 4;
            puVar8[2] = 0;
            memmove(puVar8 + 4,pcVar7 + 2,6);
          }
          *(ushort *)(iVar18 + ((uint)(param_3 + (4 - (int)puVar19)) & 0xffff)) =
               (ushort)((uVar11 + 10 & 0xff) << 8) | (ushort)(uVar11 + 10 >> 8) & 0xff;
        }
        goto LAB_0007b8ec;
      }
    }
  }
  param_2 = 0;
LAB_0007b8ec:
  if (bVar2) {
    FUN_0007b1a8(param_1,__src,uVar10,puVar19);
    return param_2;
  }
  return param_2;
}

