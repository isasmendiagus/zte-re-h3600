// module: mt7915.ko
// function: MATProto_IPv6_Tx @ 0x7c12c
// size: 2044 bytes
//

uint MATProto_IPv6_Tx(int param_1,int param_2,int param_3,void *param_4)

{
  char cVar1;
  uint *puVar2;
  byte *pbVar3;
  uint *puVar4;
  uint uVar5;
  byte bVar6;
  ushort uVar7;
  int iVar8;
  int iVar9;
  void *pvVar10;
  void *__s1;
  int iVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  char *pcVar15;
  void *__s2;
  bool bVar16;
  
  __s1 = (void *)(param_3 + 8);
  iVar9 = *(int *)(param_2 + 0xcc);
  if (__s1 == (void *)0x0) {
    printk(&_LC0,0x49);
    dump_stack();
  }
  if ((((((*(byte *)(iVar9 + 6) & 1) == 0) &&
        (((((*(byte *)(iVar9 + 6) != 0 || *(char *)(iVar9 + 7) != '\0') ||
           *(char *)(iVar9 + 8) != '\0') || *(char *)(iVar9 + 9) != '\0') ||
         *(char *)(iVar9 + 10) != '\0') || *(char *)(iVar9 + 0xb) != '\0')) &&
       (*(char *)(param_3 + 8) != -1)) &&
      ((((*(int *)(param_3 + 0xc) != 0 || *(int *)(param_3 + 8) != 0) ||
        *(int *)(param_3 + 0x10) != 0) || *(int *)(param_3 + 0x14) != 0 &&
       (iVar11 = memcmp(__s1,IPV6_LOOPBACKADDR,0x10), iVar11 != 0)))) &&
     ((pcVar15 = *(char **)(param_1 + 0xc), pcVar15 != (char *)0x0 && (*pcVar15 != '\0')))) {
    uVar12 = (byte)(*(byte *)(param_3 + 0x17) ^
                   *(byte *)(param_3 + 0x16) ^ *(byte *)(param_3 + 0x15) ^ *(byte *)(param_3 + 0x12)
                   ) & 0x3f;
    pvVar10 = *(void **)(pcVar15 + uVar12 * 4 + 4);
    __s2 = *(void **)(pcVar15 + uVar12 * 4 + 4);
    while (__s2 != (void *)0x0) {
      iVar11 = memcmp(__s1,__s2,0x10);
      if (iVar11 == 0) {
        memmove((void *)((int)__s2 + 0x10),(void *)(iVar9 + 6),6);
        *(int *)((int)__s2 + 0x18) = jiffies;
        goto LAB_0007c188;
      }
      if ((*(int *)((int)__s2 + 0x18) + 30000) - jiffies < 0) {
        if (__s2 == *(void **)(pcVar15 + uVar12 * 4 + 4)) {
          pvVar10 = *(void **)((int)__s2 + 0x1c);
          *(void **)(pcVar15 + uVar12 * 4 + 4) = pvVar10;
        }
        else {
          *(undefined4 *)((int)pvVar10 + 0x1c) = *(undefined4 *)((int)__s2 + 0x1c);
        }
        MATDBEntryFree(param_1,__s2);
        __s2 = pvVar10;
        if (pvVar10 != (void *)0x0) {
          __s2 = *(void **)((int)pvVar10 + 0x1c);
        }
        *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + -1;
      }
      else {
        pvVar10 = __s2;
        __s2 = *(void **)((int)__s2 + 0x1c);
      }
    }
    if (*(uint *)(param_1 + 0x1c) < 0x100) {
      pvVar10 = (void *)MATDBEntryAlloc(param_1,0x20);
      if (pvVar10 == (void *)0x0) {
        if (-1 < DebugLevel) {
          printk("IPv6MacTableUpdate():Insertion failed!\n");
        }
      }
      else {
        memmove(pvVar10,__s1,0x10);
        memmove((void *)((int)pvVar10 + 0x10),(void *)(iVar9 + 6),6);
        iVar9 = jiffies;
        *(undefined4 *)((int)pvVar10 + 0x1c) = 0;
        *(int *)((int)pvVar10 + 0x18) = iVar9;
        if (*(int *)(pcVar15 + uVar12 * 4 + 4) != 0) {
          *(int *)((int)pvVar10 + 0x1c) = *(int *)(pcVar15 + uVar12 * 4 + 4);
        }
        *(void **)(pcVar15 + uVar12 * 4 + 4) = pvVar10;
        *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + 1;
      }
    }
  }
LAB_0007c188:
  bVar6 = *(byte *)(param_3 + 6);
  if (bVar6 == 0x11 || bVar6 == 0x3a) {
    if (bVar6 != 0x3a) {
      return 0;
    }
    uVar7 = *(ushort *)(param_3 + 4);
    iVar9 = 0x28;
  }
  else {
    iVar9 = 0x28;
    if (bVar6 != 0x3b && bVar6 != 6) {
      do {
        pbVar3 = (byte *)(param_3 + iVar9);
        if (bVar6 == 0x2b) {
          bVar6 = *(byte *)(param_3 + iVar9);
          iVar11 = (pbVar3[1] + 1) * 8;
        }
        else {
          if (bVar6 < 0x2c) {
            if (bVar6 != 0) {
LAB_0007c208:
              if (DebugLevel < 3) {
                return 0;
              }
              printk("IPv6ExtHdrHandle failed!\n");
              return 0;
            }
          }
          else {
            if (bVar6 == 0x2c) {
              bVar6 = *pbVar3;
              iVar11 = 8;
              goto LAB_0007c1d4;
            }
            if (bVar6 != 0x3c) goto LAB_0007c208;
          }
          bVar6 = *pbVar3;
          iVar11 = (pbVar3[1] + 1) * 8;
        }
LAB_0007c1d4:
        iVar9 = iVar9 + iVar11;
        bVar16 = 0x10 < bVar6;
        if (bVar6 != 0x11) {
          bVar16 = bVar6 != 0x3a;
        }
        if (!bVar16 || (bVar6 == 0x11 || bVar6 == 0x3b)) break;
        if (bVar6 == 6) {
          return 0;
        }
      } while( true );
    }
    if (bVar6 != 0x3a) {
      return 0;
    }
    uVar7 = *(ushort *)(param_3 + 4);
  }
  iVar11 = param_3 + iVar9;
  uVar12 = ((uVar7 & 0xff) << 8 | (uint)(uVar7 >> 8)) - iVar9;
  uVar13 = uVar12 + 0x28;
  switch(*(undefined1 *)(param_3 + iVar9)) {
  case 0x85:
    if ((8 < uVar13 &&
         (((*(int *)(param_3 + 0xc) != 0 || *(int *)(param_3 + 8) != 0) ||
          *(int *)(param_3 + 0x10) != 0) || *(int *)(param_3 + 0x14) != 0)) &&
       (uVar12 = uVar12 + 0x20, 3 < uVar12)) {
      iVar8 = iVar9 + 8;
      uVar5 = (uint)*(byte *)(param_3 + iVar8 + 1);
      if (uVar5 != 0) {
        cVar1 = *(char *)(param_3 + iVar8);
        while (cVar1 != '\x01') {
          uVar12 = uVar12 + uVar5 * -8;
          iVar8 = (short)uVar5 * 8 + iVar8;
          if (uVar12 < 4) {
            return 0;
          }
          uVar5 = (uint)*(byte *)(param_3 + iVar8 + 1);
          if (uVar5 == 0) {
            return 0;
          }
          cVar1 = *(char *)(param_3 + iVar8);
        }
LAB_0007c528:
        uVar12 = *(byte *)(param_2 + 0x72) & 1;
        if ((*(byte *)(param_2 + 0x72) & 1) != 0) {
          if ((*(uint *)(*(int *)(param_2 + 0xc4) + 0x20) & 0xffff) == 1) {
            uVar12 = 0;
          }
          else {
            uVar12 = skb_copy(param_2,0x20);
            g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
            if (uVar12 != 0) {
              param_3 = *(int *)(uVar12 + 0xcc);
              if (CONCAT11(*(undefined1 *)(param_3 + 0xc),*(undefined1 *)(param_3 + 0xd)) == -0x7f00
                 ) {
                param_3 = param_3 + 0x12;
              }
              else {
                param_3 = param_3 + 0xe;
              }
              iVar11 = param_3 + iVar9;
            }
          }
        }
        memmove((void *)(param_3 + iVar8 + 2),param_4,6);
        uVar7 = 0;
        *(undefined1 *)(iVar11 + 2) = 0;
        *(undefined1 *)(iVar11 + 3) = 0;
        if ((uVar13 & 3) == 0) {
          puVar2 = (uint *)(param_3 + 4);
          puVar4 = (uint *)(param_3 + 0x14);
          uVar5 = 0;
          do {
            puVar2 = puVar2 + 1;
            uVar5 = (uint)CARRY4(uVar5,*puVar2) + uVar5 + *puVar2;
          } while (puVar2 != puVar4);
          do {
            puVar4 = puVar4 + 1;
            uVar5 = (uint)CARRY4(uVar5,*puVar4) + uVar5 + *puVar4;
          } while (puVar4 != (uint *)(param_3 + 0x24));
          uVar14 = uVar13 & 0xffff;
          uVar13 = uVar13 * 0x1000000 | (uVar14 >> 8) << 0x10;
          uVar13 = uVar13 + uVar5 + 0x3a000000 + (uint)CARRY4(uVar13,uVar5);
          if (uVar13 < 0x3a000000) {
            uVar13 = uVar13 + 1;
          }
          if (uVar14 != 0) {
            puVar2 = (uint *)(iVar11 + -4);
            iVar9 = 0;
            do {
              puVar2 = puVar2 + 1;
              iVar9 = iVar9 + 4;
              uVar13 = (uint)CARRY4(uVar13,*puVar2) + uVar13 + *puVar2;
            } while (iVar9 < (int)uVar14);
          }
          for (; uVar13 >> 0x10 != 0; uVar13 = (uVar13 >> 0x10) + (uVar13 & 0xffff)) {
          }
          uVar7 = ~(ushort)uVar13;
        }
        *(ushort *)(iVar11 + 2) = uVar7;
        return uVar12;
      }
    }
    break;
  case 0x86:
    if ((0x10 < uVar13 &&
         (((*(int *)(param_3 + 0xc) != 0 || *(int *)(param_3 + 8) != 0) ||
          *(int *)(param_3 + 0x10) != 0) || *(int *)(param_3 + 0x14) != 0)) &&
       (uVar12 = uVar12 + 0x18, 3 < uVar12)) {
      iVar8 = iVar9 + 0x10;
      uVar5 = (uint)*(byte *)(param_3 + iVar8 + 1);
      if (uVar5 != 0) {
        cVar1 = *(char *)(param_3 + iVar8);
        while (cVar1 != '\x01') {
          uVar12 = uVar12 + uVar5 * -8;
          iVar8 = (short)uVar5 * 8 + iVar8;
          if (uVar12 < 4) {
            return 0;
          }
          uVar5 = (uint)*(byte *)(param_3 + iVar8 + 1);
          if (uVar5 == 0) {
            return 0;
          }
          cVar1 = *(char *)(param_3 + iVar8);
        }
        goto LAB_0007c528;
      }
    }
    break;
  case 0x87:
    if ((0x18 < uVar13 &&
         (((*(int *)(param_3 + 0xc) != 0 || *(int *)(param_3 + 8) != 0) ||
          *(int *)(param_3 + 0x10) != 0) || *(int *)(param_3 + 0x14) != 0)) &&
       (uVar12 = uVar12 + 0x10, 3 < uVar12)) {
      iVar8 = iVar9 + 0x18;
      uVar5 = (uint)*(byte *)(param_3 + iVar8 + 1);
      if (uVar5 != 0) {
        cVar1 = *(char *)(param_3 + iVar8);
        while (cVar1 != '\x01') {
          uVar12 = uVar12 + uVar5 * -8;
          iVar8 = (short)uVar5 * 8 + iVar8;
          if (uVar12 < 4) {
            return 0;
          }
          uVar5 = (uint)*(byte *)(param_3 + iVar8 + 1);
          if (uVar5 == 0) {
            return 0;
          }
          cVar1 = *(char *)(param_3 + iVar8);
        }
        goto LAB_0007c528;
      }
    }
    break;
  case 0x88:
    if ((0x18 < uVar13 &&
         (((*(int *)(param_3 + 0xc) != 0 || *(int *)(param_3 + 8) != 0) ||
          *(int *)(param_3 + 0x10) != 0) || *(int *)(param_3 + 0x14) != 0)) &&
       (uVar12 = uVar12 + 0x10, 3 < uVar12)) {
      iVar8 = iVar9 + 0x18;
      uVar5 = (uint)*(byte *)(param_3 + iVar8 + 1);
      if (uVar5 != 0) {
        cVar1 = *(char *)(param_3 + iVar8);
        while (cVar1 != '\x02') {
          uVar12 = uVar12 + uVar5 * -8;
          iVar8 = (short)uVar5 * 8 + iVar8;
          if (uVar12 < 4) {
            return 0;
          }
          uVar5 = (uint)*(byte *)(param_3 + iVar8 + 1);
          if (uVar5 == 0) {
            return 0;
          }
          cVar1 = *(char *)(param_3 + iVar8);
        }
        goto LAB_0007c528;
      }
    }
    break;
  case 0x89:
    if ((0x28 < uVar13 &&
         (((*(int *)(param_3 + 0xc) != 0 || *(int *)(param_3 + 8) != 0) ||
          *(int *)(param_3 + 0x10) != 0) || *(int *)(param_3 + 0x14) != 0)) && (3 < uVar12)) {
      iVar8 = iVar9 + 0x28;
      uVar5 = (uint)*(byte *)(param_3 + iVar8 + 1);
      if (uVar5 != 0) {
        cVar1 = *(char *)(param_3 + iVar8);
        while (cVar1 != '\x02') {
          uVar12 = uVar12 + uVar5 * -8;
          iVar8 = (short)uVar5 * 8 + iVar8;
          if (uVar12 < 4) {
            return 0;
          }
          uVar5 = (uint)*(byte *)(param_3 + iVar8 + 1);
          if (uVar5 == 0) {
            return 0;
          }
          cVar1 = *(char *)(param_3 + iVar8);
        }
        goto LAB_0007c528;
      }
    }
    break;
  default:
    if (2 < DebugLevel) {
      printk("Un-supported ICMPv6 msg type(0x%x)! Ignore it\n");
    }
  }
  return 0;
}

