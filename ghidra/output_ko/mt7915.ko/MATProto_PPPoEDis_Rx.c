// module: mt7915.ko
// function: MATProto_PPPoEDis_Rx @ 0x7b3dc
// size: 664 bytes
//

ushort * MATProto_PPPoEDis_Rx(int param_1,int param_2,char *param_3)

{
  byte bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  ushort *puVar5;
  uint uVar6;
  char *pcVar7;
  size_t __n;
  uint uVar8;
  ushort uVar9;
  ushort *__s2;
  ushort uVar10;
  size_t sVar11;
  int local_38;
  
  if (*param_3 != '\x11') {
    return (ushort *)0x0;
  }
  bVar1 = param_3[1];
  if (bVar1 == 0x19) {
    uVar10 = 0x104;
  }
  else {
    if (0x19 < bVar1) {
      if (bVar1 != 0x65) {
        if (bVar1 != 0xa7) {
          return (ushort *)0x0;
        }
        iVar4 = *(int *)(param_2 + 0xcc);
        uVar8 = (uint)(*(ushort *)(param_3 + 2) >> 8);
        if (**(char **)(param_1 + 0x10) != '\0') {
          puVar5 = *(ushort **)(*(char **)(param_1 + 0x10) + (uVar8 & 0x3f) * 4 + 4);
          while( true ) {
            if (puVar5 == (ushort *)0x0) {
              return (ushort *)0x0;
            }
            if (((uint)*puVar5 == ((*(ushort *)(param_3 + 2) & 0xff) << 8 | uVar8)) &&
               (((((*(char *)(iVar4 + 7) == *(char *)((int)puVar5 + 3) &&
                   (char)puVar5[1] == *(char *)(iVar4 + 6)) &&
                  (char)puVar5[2] == *(char *)(iVar4 + 8)) &&
                 *(char *)(iVar4 + 9) == *(char *)((int)puVar5 + 5)) &&
                *(char *)(iVar4 + 10) == (char)puVar5[3]) &&
                *(char *)(iVar4 + 0xb) == *(char *)((int)puVar5 + 7))) break;
            puVar5 = *(ushort **)(puVar5 + 10);
          }
          if (2 < DebugLevel) {
            printk("%s(): find it! dstMac=%02x:%02x:%02x:%02x:%02x:%02x\n",
                   "getInMacByOutMacFromSesMacTb",(char)puVar5[4],*(undefined1 *)((int)puVar5 + 9),
                   (char)puVar5[5],*(undefined1 *)((int)puVar5 + 0xb),(char)puVar5[6],
                   *(undefined1 *)((int)puVar5 + 0xd));
          }
          *(undefined4 *)(puVar5 + 8) = jiffies;
          return puVar5 + 4;
        }
        return (ushort *)0x0;
      }
      uVar10 = 0x103;
      bVar2 = true;
      uVar9 = *(ushort *)(param_3 + 2) << 8 | *(ushort *)(param_3 + 2) >> 8;
      local_38 = *(int *)(param_2 + 0xcc) + 6;
      goto LAB_0007b44c;
    }
    if (bVar1 != 7) {
      return (ushort *)0x0;
    }
    uVar10 = 0x103;
  }
  uVar9 = 0;
  local_38 = 0;
  bVar2 = false;
LAB_0007b44c:
  puVar5 = (ushort *)(param_3 + 6);
  uVar8 = (*(ushort *)(param_3 + 4) & 0xff) << 8 | (uint)(*(ushort *)(param_3 + 4) >> 8);
  uVar6 = uVar8;
  while( true ) {
    if (uVar6 == 0) {
      return (ushort *)0x0;
    }
    __n = (puVar5[1] & 0xff) << 8 | (uint)(puVar5[1] >> 8);
    uVar6 = uVar6 + (0xfffc - __n) & 0xffff;
    if (uVar10 == (ushort)(*puVar5 << 8 | *puVar5 >> 8) && __n != 0) break;
    puVar5 = (ushort *)((int)puVar5 + __n + 4);
  }
  if (5 < __n) {
    __n = 6;
  }
  __s2 = puVar5 + 2;
  if (__s2 == (ushort *)0x0) {
    return (ushort *)0x0;
  }
  pcVar7 = *(char **)(param_1 + 0x14);
  if (pcVar7 == (char *)0x0) {
    return (ushort *)0x0;
  }
  if (*pcVar7 == '\0') {
    return (ushort *)0x0;
  }
  uVar6 = 0;
  sVar11 = __n;
  do {
    sVar11 = sVar11 - 1 & 0xffff;
    uVar6 = uVar6 ^ *(byte *)((int)__s2 + sVar11);
  } while (sVar11 != 0);
  iVar4 = *(int *)(pcVar7 + (uVar6 & 0x3f) * 4 + 4);
  if (iVar4 == 0) {
    return (ushort *)0x0;
  }
  while (iVar3 = memcmp((void *)(iVar4 + 2),__s2,__n), iVar3 != 0) {
    iVar4 = *(int *)(iVar4 + 0x14);
    if (iVar4 == 0) {
      return (ushort *)0x0;
    }
  }
  *(undefined4 *)(iVar4 + 0x10) = jiffies;
  if (*(char *)(iVar4 + 1) != '\0') {
    iVar3 = __n + 4;
    sVar11 = ((*(int *)(param_2 + 0xcc) - (int)__s2) + *(int *)(param_2 + 100)) - iVar3;
    if (sVar11 == 0) {
      skb_trim(param_2,*(int *)(param_2 + 100) - iVar3);
    }
    else {
      memmove(puVar5,(char *)((int)__s2 + __n),sVar11);
      skb_trim(param_2,*(int *)(param_2 + 100) - iVar3);
    }
    uVar8 = uVar8 - iVar3;
    *(ushort *)(param_3 + 4) = (ushort)((uVar8 & 0xff) << 8) | (ushort)(uVar8 >> 8) & 0xff;
  }
  if (!bVar2) {
    return (ushort *)(iVar4 + 8);
  }
  FUN_0007b1a8(param_1,(ushort *)(iVar4 + 8),uVar9,local_38);
  return (ushort *)(iVar4 + 8);
}

