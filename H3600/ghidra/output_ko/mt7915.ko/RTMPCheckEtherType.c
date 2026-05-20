// module: mt7915.ko
// function: RTMPCheckEtherType @ 0xc6f70
// size: 2020 bytes
//

undefined4 RTMPCheckEtherType(int param_1,int param_2,int param_3,int param_4)

{
  byte bVar1;
  ushort uVar2;
  bool bVar3;
  int iVar4;
  byte bVar5;
  ushort uVar6;
  uint uVar7;
  ushort uVar8;
  uint uVar9;
  int iVar10;
  ushort *puVar11;
  ushort *puVar12;
  undefined1 uVar13;
  uint uVar14;
  undefined1 uVar15;
  uint uVar16;
  bool bVar17;
  
  iVar10 = *(int *)(param_2 + 0xcc);
  uVar2 = *(ushort *)(param_3 + 8);
  if (iVar10 == 0) {
    printk(&_LC10,0x846);
    dump_stack();
    *(undefined1 *)(param_2 + 0x30) = 0;
    uVar16 = (uint)CONCAT11(DAT_0000000c,DAT_0000000d);
    if (*(char *)(param_4 + 0x8f8) == '\0') {
      return 0;
    }
LAB_000c6fb4:
    if (uVar16 == 0x8100) {
      if (iVar10 == 0) {
        return 0;
      }
    }
    else {
      if (*(short *)(param_4 + 0x8fe) == 4) {
        if (iVar10 == 0) {
          return 0;
        }
        goto LAB_000c7054;
      }
      param_2 = RtmpOsVLANInsertTag(param_2,*(ushort *)(param_4 + 0x8fa) |
                                            *(short *)(param_4 + 0x8fc) << 0xd);
      if (param_2 != 0) {
        iVar10 = *(int *)(param_2 + 0xcc);
      }
      if (iVar10 == 0) {
        printk(&_LC10,0x853);
        dump_stack();
        return 0;
      }
    }
    puVar11 = (ushort *)(iVar10 + 0xe);
LAB_000c7000:
    if (*(ushort *)(param_4 + 0x8fa) != 0) {
      uVar6 = *puVar11;
      if (*(ushort *)(param_4 + 0x8fa) == (ushort)((uVar6 & 0xf) << 8 | uVar6 >> 8)) {
        *puVar11 = uVar6 & 0xff1f;
        *puVar11 = uVar6 & 0xff1f | (*(ushort *)(param_4 + 0x8fc) & 7) << 5;
      }
      else {
        switch(*(undefined2 *)(param_4 + 0x8fe)) {
        case 0:
        case 4:
          if (0 < DebugLevel) {
            printk("%s():Allow the packet\n","RTMPCheckEtherType");
          }
          break;
        case 1:
          if (DebugLevel < 1) {
            return 0;
          }
          printk("%s():Drop the packet\n","RTMPCheckEtherType");
          return 0;
        case 2:
          if (0 < DebugLevel) {
            printk("%s():Replace the packet VLAN ID\n","RTMPCheckEtherType");
            uVar6 = *puVar11;
          }
          *puVar11 = uVar6 & 0xf0;
          *puVar11 = uVar6 & 0xf0 |
                     *(ushort *)(param_4 + 0x8fa) << 8 | *(ushort *)(param_4 + 0x8fa) >> 8;
          break;
        case 3:
          if (0 < DebugLevel) {
            printk("%s():Replace the packet VLAN Tag\n","RTMPCheckEtherType");
            uVar6 = *puVar11;
          }
          *puVar11 = uVar6 & 0xff1f;
          uVar6 = uVar6 & 0x10 | (*(ushort *)(param_4 + 0x8fc) & 7) << 5;
          *puVar11 = uVar6;
          *puVar11 = uVar6 | *(ushort *)(param_4 + 0x8fa) << 8 | *(ushort *)(param_4 + 0x8fa) >> 8;
          break;
        default:
          if (DebugLevel < 0) {
            return 0;
          }
          printk("%s(): Unexpected checking policy\n","RTMPCheckEtherType");
          return 0;
        }
      }
    }
    if (param_2 != 0) {
      *(byte *)(param_2 + 0x30) = *(byte *)(param_2 + 0x30) | 0x10;
    }
    puVar12 = puVar11 + 2;
    uVar14 = (uint)(byte)((byte)*puVar11 >> 5);
    uVar16 = (uint)*(byte *)((int)puVar11 + 3) + (uint)(byte)puVar11[1] * 0x100 & 0xffff;
LAB_000c70d4:
    if (param_2 == 0) {
      return 0;
    }
    uVar13 = (undefined1)uVar16;
    if (uVar16 < 0x8865) {
      if (uVar16 < 0x8863) {
        if (uVar16 == 0x806) {
          if ((*(int *)(param_4 + 0x14) == 1) &&
             (iVar10 = *(int *)(param_4 + 4), *(char *)(iVar10 + 0x4c9c) != '\0')) {
            iVar4 = IsIPv4ProxyARPCandidate(param_1,puVar12 + -1);
            if (iVar4 != 0) {
              iVar10 = IPv4ProxyARP(param_1,iVar10,puVar12 + -1,1,0);
              if (iVar10 != 0) {
                return 0;
              }
              if (DebugLevel < 3) {
                return 0;
              }
              printk("Can not find proxy entry\n");
              return 0;
            }
          }
          uVar15 = 8;
          *(undefined1 *)(param_2 + 0x36) = 2;
          uVar13 = 6;
          *(byte *)(param_2 + 0x4e) = *(byte *)(param_2 + 0x4e) | 10;
          uVar16 = 0;
        }
        else {
          if (uVar16 == 0x86dd) goto LAB_000c7258;
          if (uVar16 == 0x800) goto LAB_000c73b0;
LAB_000c7114:
          uVar15 = (undefined1)(uVar16 >> 8);
          uVar16 = 0;
        }
      }
      else {
        uVar15 = 0x88;
        *(undefined1 *)(param_2 + 0x36) = 2;
        *(byte *)(param_2 + 0x3f) = *(byte *)(param_2 + 0x3f) | 1;
        uVar16 = 0;
      }
    }
    else if (uVar16 == 0x888e) {
      uVar15 = 0x88;
      *(undefined1 *)(param_2 + 0x36) = 2;
      *(byte *)(param_2 + 0x30) = *(byte *)(param_2 + 0x30) | 2;
      uVar13 = 0x8e;
      *(byte *)(param_2 + 0x4e) = *(byte *)(param_2 + 0x4e) | 8;
      uVar16 = 0;
    }
    else {
      if (uVar16 != 0x893a) goto LAB_000c7114;
      uVar15 = 0x89;
      *(undefined1 *)(param_2 + 0x36) = 2;
      uVar13 = 0x3a;
      *(byte *)(param_2 + 0x4e) = *(byte *)(param_2 + 0x4e) | 8;
      uVar16 = 0;
    }
  }
  else {
    *(undefined1 *)(param_2 + 0x30) = 0;
    uVar16 = (uint)CONCAT11(*(undefined1 *)(iVar10 + 0xc),*(undefined1 *)(iVar10 + 0xd));
    if (*(char *)(param_4 + 0x8f8) != '\0') goto LAB_000c6fb4;
LAB_000c7054:
    if (uVar16 < 0x5dd) {
      if (*(char *)(iVar10 + 0xe) != -0x56) {
        return 0;
      }
      if (*(char *)(iVar10 + 0xf) != -0x56) {
        return 0;
      }
      if (*(char *)(iVar10 + 0x10) != '\x03') {
        return 0;
      }
      bVar5 = *(byte *)(iVar10 + 0x14);
      bVar1 = *(byte *)(iVar10 + 0x15);
      puVar12 = (ushort *)(iVar10 + 0x16);
      if (param_2 != 0) {
        *(undefined1 *)(param_2 + 0x30) = 0x20;
      }
      uVar16 = (uint)bVar1 + (uint)bVar5 * 0x100 & 0xffff;
    }
    else {
      puVar12 = (ushort *)(iVar10 + 0xe);
    }
    puVar11 = puVar12;
    if (uVar16 == 0x8100) goto LAB_000c7000;
    if (uVar16 == 0x800) {
      uVar14 = (uint)(*(byte *)((int)puVar12 + 1) >> 5);
      if (param_2 == 0) {
        return 0;
      }
LAB_000c73b0:
      if (*(uint *)(param_2 + 100) < 0x23) {
        printk(&_LC55,0x93d);
        dump_stack();
      }
      bVar5 = *(byte *)(param_2 + 0x30);
      *(byte *)(param_2 + 0x30) = bVar5 | 4;
      uVar16 = (uint)*(byte *)((int)puVar12 + 9);
      if (uVar16 == 1) {
        uVar15 = 8;
        *(undefined1 *)(param_2 + 0x36) = 2;
        uVar13 = 0;
        *(byte *)(param_2 + 0x4e) = *(byte *)(param_2 + 0x4e) | 9;
      }
      else if (uVar16 == 0x11) {
        uVar6 = puVar12[10] << 8 | puVar12[10] >> 8;
        uVar8 = puVar12[0xb] << 8 | puVar12[0xb] >> 8;
        if ((uVar8 == 0x43 && uVar6 == 0x44) || (uVar8 == 0x44 && uVar6 == 0x43)) {
          *(byte *)(param_2 + 0x30) = bVar5 | 5;
          *(undefined1 *)(param_2 + 0x36) = 2;
          *(byte *)(param_2 + 0x4e) = *(byte *)(param_2 + 0x4e) | 8;
        }
        uVar13 = 0;
        WNMIPv4ProxyARPCheck(param_1,param_2,uVar6,uVar8,puVar12 + 10,0);
        uVar15 = 8;
      }
      else {
        uVar15 = 8;
        uVar13 = 0;
      }
    }
    else {
      if (uVar16 != 0x86dd) {
        uVar14 = 0;
        goto LAB_000c70d4;
      }
      uVar14 = ((uint)(byte)*puVar12 << 0x1c) >> 0x1d;
      if (param_2 == 0) {
        return 0;
      }
LAB_000c7258:
      if (*(int *)(param_4 + 0x14) == 1) {
        iVar10 = *(int *)(param_4 + 4);
        WNMIPv6ProxyARPCheck(param_1,param_2,puVar12,0);
        if (*(char *)(iVar10 + 0x4c9c) != '\0') {
          iVar4 = IsIPv6ProxyARPCandidate(param_1,puVar12 + -1);
          if (iVar4 != 0) {
            iVar10 = IPv6ProxyARP(param_1,iVar10,puVar12 + -1,1,0);
            if (iVar10 != 0) {
              return 0;
            }
            if (DebugLevel < 3) {
              return 0;
            }
            printk("Can not find IPv6 proxy entry\n");
            return 0;
          }
        }
      }
      uVar15 = 0x86;
      uVar16 = (uint)(byte)puVar12[3];
      uVar13 = 0xdd;
      if ((*puVar12 & 0xf0) != 0x60) {
        uVar14 = 0;
      }
    }
  }
  *(undefined1 *)(param_2 + 0x34) = uVar13;
  *(undefined1 *)(param_2 + 0x35) = uVar15;
  iVar10 = (uint)uVar2 * 0x14c0;
  if (*(short *)(param_4 + 0x8d4) == 0x101) {
    uVar14 = (uint)*(byte *)(param_4 + 0x8d6);
    *(byte *)(param_2 + 0x2a) = *(byte *)(param_4 + 0x8d6);
  }
  if (param_1 + iVar10 + 0xa1d20 != 0) {
    iVar10 = param_1 + iVar10;
    uVar7 = *(uint *)(iVar10 + 0xa29ec);
    if (uVar7 != 0xffffffff) {
      uVar9 = *(uint *)(iVar10 + 0xa29f0);
      if (uVar9 == 0) {
        *(char *)(param_2 + 0x2a) = (char)uVar7;
        uVar14 = uVar7 & 0xff;
      }
      else if (uVar9 == uVar16) {
        *(char *)(param_2 + 0x2a) = (char)uVar7;
        uVar14 = uVar7 & 0xff;
      }
    }
  }
  bVar17 = uVar14 == 7;
  if (uVar14 < 8) {
    bVar17 = *(char *)(param_4 + 0x8d4) == '\x01';
  }
  bVar3 = *(char *)(param_4 + 0x8d4) == '\x01';
  if (((bVar17) && ((*(byte *)(param_2 + 0x4e) & 8) != 0)) && (uVar14 == 0 || uVar14 == 3)) {
    uVar14 = (uint)(byte)(&DAT_00294e00)[*(byte *)(param_1 + 0xa7beca)];
  }
  bVar5 = *(byte *)((int)&WMM_UP2AC_MAP + uVar14);
  if ((*(char *)(param_1 + (uint)bVar5 + 0x7950a0) == '\0') &&
     ((*(int *)(param_4 + 0x14) != 0x100 && *(int *)(param_4 + 0x14) != 2 ||
      (*(char *)((uint)uVar2 * 0x14c0 + param_1 + (uint)bVar5 + 0xa30dc) == '\0')))) {
    uVar13 = uVar14 < 8 && bVar3;
    if (uVar14 < 8 && bVar3) {
      uVar13 = (undefined1)uVar14;
      goto LAB_000c7228;
    }
  }
  else {
    uVar13 = false;
    if (bVar3) {
      uVar13 = 0;
      bVar5 = (byte)WMM_UP2AC_MAP;
      goto LAB_000c7228;
    }
  }
  bVar5 = 1;
LAB_000c7228:
  *(undefined1 *)(param_2 + 0x2a) = uVar13;
  *(byte *)(param_2 + 0x4d) = bVar5;
  return 1;
}

