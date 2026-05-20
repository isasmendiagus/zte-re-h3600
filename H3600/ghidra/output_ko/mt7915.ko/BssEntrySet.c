// module: mt7915.ko
// function: BssEntrySet @ 0x10e8b4
// size: 3396 bytes
//

void BssEntrySet(undefined4 param_1,undefined4 param_2,int param_3,int param_4,undefined1 param_5,
                ushort param_6,char *param_7)

{
  char cVar1;
  undefined2 uVar2;
  ushort uVar3;
  byte bVar4;
  undefined1 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  byte *pbVar9;
  size_t sVar10;
  int iVar11;
  uint uVar12;
  byte *pbVar13;
  byte *pbVar14;
  short sVar15;
  uint uVar16;
  uint uVar17;
  uint __n;
  char *__s1;
  byte *local_44;
  byte local_29 [5];
  
  *(undefined4 *)(param_3 + 6) = *(undefined4 *)(param_4 + 6);
  uVar2 = *(undefined2 *)(param_4 + 10);
  *(undefined1 *)(param_3 + 0x85) = 1;
  *(undefined2 *)(param_3 + 10) = uVar2;
  __n = (uint)param_6;
  *(undefined1 *)(param_3 + 0x86) = *(undefined1 *)(param_4 + 0xa4);
  if (*(byte *)(param_4 + 0x2c) == 0) {
    iVar6 = memcmp((void *)(param_3 + 0x95),ZeroSsid,(uint)*(byte *)(param_3 + 0x94));
    if (iVar6 == 0) {
      __memzero((void *)(param_3 + 0x95),0x20);
      *(undefined1 *)(param_3 + 0x94) = 0;
    }
  }
  else {
    iVar6 = memcmp((void *)(param_4 + 0xc),ZeroSsid,(uint)*(byte *)(param_4 + 0x2c));
    if (iVar6 != 0) {
      __memzero((void *)(param_3 + 0x95),0x20);
      memmove((void *)(param_3 + 0x95),(void *)(param_4 + 0xc),(uint)*(byte *)(param_4 + 0x2c));
      uVar5 = *(undefined1 *)(param_4 + 0x2c);
      *(undefined1 *)(param_3 + 0x85) = 0;
      *(undefined1 *)(param_3 + 0x94) = uVar5;
    }
  }
  *(undefined1 *)(param_3 + 0x14) = *(undefined1 *)(param_4 + 0x2d);
  *(undefined2 *)(param_3 + 0x18) = *(undefined2 *)(param_4 + 0x2e);
  if (*(char *)(param_4 + 0x2d) == '\x01') {
    if (*(char *)(param_4 + 0x48) != '\0') {
      *(ushort *)(param_3 + 0x8c) = (ushort)*(byte *)(param_4 + 0x49);
      *(ushort *)(param_3 + 0x8e) = (ushort)*(byte *)(param_4 + 0x4a);
      *(undefined2 *)(param_3 + 0x90) = *(undefined2 *)(param_4 + 0x4b);
      *(undefined2 *)(param_3 + 0x92) = *(undefined2 *)(param_4 + 0x4d);
    }
  }
  else {
    *(undefined2 *)(param_3 + 0x16) = *(undefined2 *)(param_4 + 0x32);
  }
  *(undefined4 *)(param_3 + 0xbc) = jiffies;
  uVar3 = *(ushort *)(param_4 + 0x34);
  *(byte *)(param_3 + 0x84) = (byte)(((uint)uVar3 << 0x1b) >> 0x1f);
  *(ushort *)(param_3 + 0x8a) = uVar3;
  sVar10 = (size_t)*(byte *)(param_4 + 0xac);
  if (0xc < sVar10) {
    printk(&_LC0,0x29f);
    dump_stack();
    sVar10 = (size_t)*(byte *)(param_4 + 0xac);
    if (0xc < sVar10) {
      sVar10 = 0xc;
      *(undefined1 *)(param_4 + 0xac) = 0xc;
    }
  }
  memmove((void *)(param_3 + 0x1a),(void *)(param_4 + 0xad),sVar10);
  *(undefined1 *)(param_3 + 0x26) = *(undefined1 *)(param_4 + 0xac);
  sVar10 = (size_t)*(byte *)(param_4 + 0xb9);
  if (0xc < sVar10) {
    printk(&_LC1,0x2a6);
    dump_stack();
    sVar10 = (size_t)*(byte *)(param_4 + 0xb9);
    if (0xc < sVar10) {
      sVar10 = 0xc;
      *(undefined1 *)(param_4 + 0xb9) = 0xc;
    }
  }
  memmove((void *)(param_3 + 0x27),(void *)(param_4 + 0xba),sVar10);
  *(undefined1 *)(param_3 + 0x70) = *(undefined1 *)(param_4 + 0xa3);
  *(undefined1 *)(param_3 + 0x33) = *(undefined1 *)(param_4 + 0xb9);
  *(undefined1 *)(param_3 + 0x34) = *(undefined1 *)(param_4 + 0x36);
  *(undefined1 *)(param_3 + 0xc) = *(undefined1 *)(param_4 + 0x30);
  uVar5 = *(undefined1 *)(param_4 + 0x30);
  *(undefined1 *)(param_3 + 0x71) = param_5;
  *(undefined1 *)(param_3 + 0xd) = uVar5;
  *(undefined1 *)(param_3 + 0x4f5) = *(undefined1 *)(param_4 + 0x3b);
  memmove((void *)(param_3 + 0xd2),(void *)(param_4 + 0x40),8);
  *(undefined2 *)(param_3 + 0xda) = *(undefined2 *)(param_4 + 0x2e);
  uVar2 = *(undefined2 *)(param_4 + 0x34);
  *(ushort *)(param_3 + 0xec) = param_6;
  *(undefined2 *)(param_3 + 0xdc) = uVar2;
  if (__n != 0) {
    memmove((void *)(param_3 + 0xee),param_7,__n);
  }
  uVar17 = *(uint *)(param_3 + 0xac8) & 0xfffffffc;
  *(uint *)(param_3 + 0xac8) = uVar17;
  uVar16 = *(uint *)(param_4 + 0xa8);
  if ((uVar16 & 1) == 0) {
LAB_0010ea10:
    if ((uVar16 & 0x10) != 0) {
      memmove((void *)(param_3 + 0xace),(void *)(param_4 + 0x122),0x15);
      memmove((void *)(param_3 + 0xae3),(void *)(param_4 + 0x137),4);
      memmove((void *)(param_3 + 0xae7),(void *)(param_4 + 0x13b),4);
      *(uint *)(param_3 + 0xac8) = *(uint *)(param_3 + 0xac8) | 0x10;
      uVar16 = *(uint *)(param_4 + 0xa8);
    }
    if ((uVar16 & 0x20) != 0) {
      memmove((void *)(param_3 + 0xaeb),(void *)(param_4 + 0x13f),6);
      *(uint *)(param_3 + 0xac8) = *(uint *)(param_3 + 0xac8) | 0x20;
    }
  }
  else {
    *(uint *)(param_3 + 0xac8) = uVar17 | 1;
    memmove((void *)(param_3 + 0x35),(void *)(param_4 + 0xdc),0x1a);
    uVar16 = *(uint *)(param_4 + 0xa8);
    if ((uVar16 & 2) != 0) {
      *(uint *)(param_3 + 0xac8) = uVar17 | 3;
      memmove((void *)(param_3 + 0x4f),(void *)(param_4 + 0xf6),0x16);
      uVar5 = get_cent_ch_by_htinfo(param_1,(void *)(param_4 + 0xf6),(void *)(param_4 + 0xdc));
      *(undefined1 *)(param_3 + 0xd) = uVar5;
      uVar16 = *(uint *)(param_4 + 0xa8);
    }
    if ((uVar16 & 4) != 0) {
      memmove((void *)(param_3 + 0x72),(void *)(param_4 + 0x10c),0xc);
      *(uint *)(param_3 + 0xac8) = *(uint *)(param_3 + 0xac8) | 4;
      uVar16 = *(uint *)(param_4 + 0xa8);
    }
    if ((uVar16 & 8) != 0) {
      memmove((void *)(param_3 + 0x7e),(void *)(param_4 + 0x118),5);
      *(uint *)(param_3 + 0xac8) = *(uint *)(param_3 + 0xac8) | 8;
      if ((((*(char *)(param_4 + 0x118) != '\0') && ((*(byte *)(param_4 + 0xf7) & 3) != 0)) &&
          ((*(byte *)(param_4 + 0xdc) & 2) != 0)) &&
         (*(char *)(param_4 + 0xf6) != *(char *)(param_3 + 0xd))) {
        if (3 < DebugLevel) {
          printk("%s():VHT vht_op_info->center_freq_1=%d, Bss->CentCh=%d, change from CentralChannel to cent_ch!\n"
                 ,"BssEntrySet",*(undefined1 *)(param_4 + 0x119));
        }
        *(undefined1 *)(param_3 + 0xd) = *(undefined1 *)(param_4 + 0x119);
      }
      uVar16 = *(uint *)(param_4 + 0xa8);
    }
    if ((uVar16 & 0x10) != 0) {
      uVar17 = *(uint *)(param_3 + 0xac8) | 0x10;
      *(uint *)(param_3 + 0xac8) = uVar17;
      uVar16 = *(uint *)(param_4 + 0xa8);
      if ((uVar16 & 0x20) != 0) goto LAB_0010f11c;
      goto LAB_0010ea10;
    }
    if ((uVar16 & 0x20) != 0) {
      uVar17 = *(uint *)(param_3 + 0xac8);
LAB_0010f11c:
      *(uint *)(param_3 + 0xac8) = uVar17 | 0x20;
      uVar16 = *(uint *)(param_4 + 0xa8);
      goto LAB_0010ea10;
    }
  }
  uVar17 = (uint)*(ushort *)(param_3 + 0xec);
  local_29[0] = 0;
  *(undefined4 *)(param_3 + 0xc4) = 0;
  *(undefined4 *)(param_3 + 200) = 0;
  *(undefined4 *)(param_3 + 0xcc) = 0;
  iVar6 = (int)(short)*(ushort *)(param_3 + 0xec);
  uVar16 = uVar17;
  if (0 < iVar6) {
    do {
      iVar6 = param_3 + (uVar17 - iVar6) + 0xe8;
      if (*(char *)(iVar6 + 6) == '0') {
        iVar7 = wpa_rsne_sanity(iVar6 + 6,*(char *)(iVar6 + 7) + '\x02',local_29);
        bVar4 = local_29[0];
        if (iVar7 != 0) {
          if (local_29[0] == 0) {
            *(uint *)(param_3 + 0xcc) = *(uint *)(param_3 + 0xcc) | 0x20;
LAB_0010ec20:
            *(uint *)(param_3 + 200) = *(uint *)(param_3 + 200) | 0x20;
LAB_0010ec2c:
            *(uint *)(param_3 + 0xc4) = *(uint *)(param_3 + 0xc4) | 0x40;
          }
          else {
            if (local_29[0] < 2) goto LAB_0010ec20;
            if (local_29[0] == 2) goto LAB_0010ec2c;
          }
          if ((*(short *)(iVar6 + 8) == 1 && local_29[0] != 0) &&
             (iVar7 = memcmp((void *)(iVar6 + 10),&RSN_OUI,3), iVar7 == 0)) {
            switch(*(undefined1 *)(iVar6 + 0xd)) {
            case 1:
              *(uint *)(param_3 + 0xcc) = *(uint *)(param_3 + 0xcc) | 2;
              break;
            case 2:
              *(uint *)(param_3 + 0xcc) = *(uint *)(param_3 + 0xcc) | 0x10;
              break;
            case 4:
              *(uint *)(param_3 + 0xcc) = *(uint *)(param_3 + 0xcc) | 0x20;
              break;
            case 5:
              *(uint *)(param_3 + 0xcc) = *(uint *)(param_3 + 0xcc) | 4;
              break;
            case 8:
              *(uint *)(param_3 + 0xcc) = *(uint *)(param_3 + 0xcc) | 0x80;
              break;
            case 9:
              *(uint *)(param_3 + 0xcc) = *(uint *)(param_3 + 0xcc) | 0x100;
              break;
            case 10:
              *(uint *)(param_3 + 0xcc) = *(uint *)(param_3 + 0xcc) | 0x40;
            }
            if (1 < bVar4) {
              pbVar13 = (byte *)(iVar6 + 0x10);
              sVar15 = (ushort)*(byte *)(iVar6 + 0xe) + (ushort)*(byte *)(iVar6 + 0xf) * 0x100;
              if (sVar15 != 0) {
                pbVar9 = pbVar13 + ((ushort)(sVar15 - 1) + 1) * 4;
                pbVar14 = pbVar13;
                do {
                  switch(pbVar14[3]) {
                  case 1:
                    *(uint *)(param_3 + 200) = *(uint *)(param_3 + 200) | 2;
                    break;
                  case 2:
                    *(uint *)(param_3 + 200) = *(uint *)(param_3 + 200) | 0x10;
                    break;
                  case 4:
                    *(uint *)(param_3 + 200) = *(uint *)(param_3 + 200) | 0x20;
                    break;
                  case 5:
                    *(uint *)(param_3 + 200) = *(uint *)(param_3 + 200) | 4;
                    break;
                  case 8:
                    *(uint *)(param_3 + 200) = *(uint *)(param_3 + 200) | 0x80;
                    break;
                  case 9:
                    *(uint *)(param_3 + 200) = *(uint *)(param_3 + 200) | 0x100;
                    break;
                  case 10:
                    *(uint *)(param_3 + 200) = *(uint *)(param_3 + 200) | 0x40;
                  }
                  pbVar14 = pbVar14 + 4;
                  pbVar13 = pbVar9;
                } while (pbVar14 != pbVar9);
              }
              if (bVar4 != 2) {
                pbVar14 = pbVar13 + 2;
                sVar15 = (ushort)*pbVar13 + (ushort)pbVar13[1] * 0x100;
                local_44 = pbVar14;
                if (sVar15 != 0) {
                  do {
                    iVar7 = memcmp(pbVar14,&RSN_OUI,3);
                    local_44 = pbVar14;
                    if (iVar7 != 0) break;
                    switch(pbVar14[3]) {
                    case 0:
                      *(uint *)(param_3 + 0xc4) = *(uint *)(param_3 + 0xc4) | 0x20;
                      break;
                    case 1:
                      *(uint *)(param_3 + 0xc4) = *(uint *)(param_3 + 0xc4) | 0x40;
                      break;
                    case 2:
                      *(uint *)(param_3 + 0xc4) = *(uint *)(param_3 + 0xc4) | 0x80;
                      break;
                    case 3:
                      *(uint *)(param_3 + 0xc4) = *(uint *)(param_3 + 0xc4) | 0x100;
                      break;
                    case 4:
                      *(uint *)(param_3 + 0xc4) = *(uint *)(param_3 + 0xc4) | 0x200;
                      break;
                    case 5:
                      *(undefined1 *)(param_3 + 0x4f4) = 1;
                      *(uint *)(param_3 + 0xc4) = *(uint *)(param_3 + 0xc4) | 0x40;
                      break;
                    case 6:
                      *(undefined1 *)(param_3 + 0x4f4) = 1;
                      *(uint *)(param_3 + 0xc4) = *(uint *)(param_3 + 0xc4) | 0x80;
                      break;
                    case 7:
                      *(uint *)(param_3 + 0xc4) = *(uint *)(param_3 + 0xc4) | 0x1000;
                      break;
                    case 8:
                      *(uint *)(param_3 + 0xc4) = *(uint *)(param_3 + 0xc4) | 0x2000;
                      break;
                    case 9:
                      *(uint *)(param_3 + 0xc4) = *(uint *)(param_3 + 0xc4) | 0x4000;
                      break;
                    case 0xb:
                      *(uint *)(param_3 + 0xc4) = *(uint *)(param_3 + 0xc4) | 0x8000;
                      break;
                    case 0xc:
                      *(uint *)(param_3 + 0xc4) = *(uint *)(param_3 + 0xc4) | 0x10000;
                      break;
                    case 0xd:
                      *(uint *)(param_3 + 0xc4) = *(uint *)(param_3 + 0xc4) | 0x20000;
                      break;
                    case 0x12:
                      *(uint *)(param_3 + 0xc4) = *(uint *)(param_3 + 0xc4) | 0x100000;
                    }
                    pbVar14 = pbVar14 + 4;
                    local_44 = pbVar13 + (uint)(ushort)(sVar15 - 1) * 4 + 6;
                  } while (pbVar14 != pbVar13 + (uint)(ushort)(sVar15 - 1) * 4 + 6);
                }
                if (*(char *)(param_3 + 0x14) == '\0') {
                  *(uint *)(param_3 + 0xc4) = *(uint *)(param_3 + 0xc4) | 0x20;
                }
                if (bVar4 != 3) {
                  *(ushort *)(param_3 + 0xd0) = (ushort)*local_44 + (ushort)local_44[1] * 0x100;
                }
              }
            }
          }
        }
      }
      else if (*(char *)(iVar6 + 6) == -0x23) {
        iVar7 = memcmp((void *)(iVar6 + 8),&SES_OUI,3);
        if ((iVar7 == 0) && (*(char *)(iVar6 + 7) == '\a')) {
          *(undefined1 *)(param_3 + 0xc0) = 1;
        }
        else {
          iVar7 = memcmp((void *)(iVar6 + 8),&WPA_OUI,4);
          if (iVar7 == 0) {
            switch(*(undefined1 *)(iVar6 + 0x11)) {
            case 1:
              *(uint *)(param_3 + 0xcc) = *(uint *)(param_3 + 0xcc) | 2;
              break;
            case 2:
              *(uint *)(param_3 + 0xcc) = *(uint *)(param_3 + 0xcc) | 0x10;
              break;
            case 4:
              *(uint *)(param_3 + 0xcc) = *(uint *)(param_3 + 0xcc) | 0x20;
              break;
            case 5:
              *(uint *)(param_3 + 0xcc) = *(uint *)(param_3 + 0xcc) | 4;
            }
            iVar7 = iVar6 + 0x14;
            sVar15 = (ushort)*(byte *)(iVar6 + 0x12) + (ushort)*(byte *)(iVar6 + 0x13) * 0x100;
            if (sVar15 != 0) {
              iVar8 = iVar7 + ((ushort)(sVar15 - 1) + 1) * 4;
              iVar11 = iVar7;
              do {
                switch(*(undefined1 *)(iVar11 + 3)) {
                case 1:
                  *(uint *)(param_3 + 200) = *(uint *)(param_3 + 200) | 2;
                  break;
                case 2:
                  *(uint *)(param_3 + 200) = *(uint *)(param_3 + 200) | 0x10;
                  break;
                case 4:
                  *(uint *)(param_3 + 200) = *(uint *)(param_3 + 200) | 0x20;
                  break;
                case 5:
                  *(uint *)(param_3 + 200) = *(uint *)(param_3 + 200) | 4;
                }
                iVar11 = iVar11 + 4;
                iVar7 = iVar8;
              } while (iVar11 != iVar8);
            }
            if (*(char *)(iVar7 + 5) == '\x01') {
              *(uint *)(param_3 + 0xc4) = *(uint *)(param_3 + 0xc4) | 8;
            }
            else if (*(char *)(iVar7 + 5) == '\x02') {
              *(uint *)(param_3 + 0xc4) = *(uint *)(param_3 + 0xc4) | 0x10;
            }
            if (*(char *)(param_3 + 0x14) == '\0') {
              *(uint *)(param_3 + 0xc4) = *(uint *)(param_3 + 0xc4) | 0x20;
            }
          }
        }
      }
      uVar16 = uVar16 + (0xfffe - (uint)*(byte *)(iVar6 + 7));
      iVar6 = (int)(short)uVar16;
      if (iVar6 < 1) goto LAB_0010eca8;
      uVar17 = (uint)*(ushort *)(param_3 + 0xec);
      uVar16 = uVar16 & 0xffff;
    } while( true );
  }
LAB_0010ecb4:
  *(undefined4 *)(param_3 + 0xc4) = 1;
  if (*(char *)(param_3 + 0x84) == '\0') {
    uVar16 = *(uint *)(param_3 + 0xcc) | 1;
    *(uint *)(param_3 + 200) = *(uint *)(param_3 + 200) | 1;
  }
  else {
    uVar16 = *(uint *)(param_3 + 0xcc) | 0xe;
    *(undefined4 *)(param_3 + 0xc4) = 3;
    *(uint *)(param_3 + 200) = *(uint *)(param_3 + 200) | 0xe;
  }
  *(uint *)(param_3 + 0xcc) = uVar16;
LAB_0010ecf4:
  if (*(char *)(param_4 + 0x50) == '\0') {
    *(undefined1 *)(param_3 + 0x502) = 0;
    if (*(char *)(param_4 + 0x7c) != '\0') goto LAB_0010f164;
    *(undefined1 *)(param_3 + 0x526) = 0;
LAB_0010ed14:
    if (*(char *)(param_4 + 0x74) == '\0') {
      *(undefined1 *)(param_3 + 0x52c) = 0;
      goto LAB_0010ed24;
    }
  }
  else {
    memmove((void *)(param_3 + 0x502),(void *)(param_4 + 0x50),0x24);
    if (*(char *)(param_4 + 0x7c) == '\0') {
      *(undefined1 *)(param_3 + 0x526) = 0;
      goto LAB_0010ed14;
    }
LAB_0010f164:
    memmove((void *)(param_3 + 0x526),(void *)(param_4 + 0x7c),5);
    if (*(char *)(param_4 + 0x74) == '\0') {
      *(undefined1 *)(param_3 + 0x52c) = 0;
      goto LAB_0010ed24;
    }
  }
  memmove((void *)(param_3 + 0x52c),(void *)(param_4 + 0x74),8);
LAB_0010ed24:
  uVar16 = 0;
  *(undefined2 *)(param_3 + 0x536) = 0xffff;
  *(undefined1 *)(param_3 + 0x534) = 0;
  __memzero((void *)(param_3 + 0x539),0x80);
  __memzero((void *)(param_3 + 0x5ba),0x80);
  __memzero((void *)(param_3 + 0x63b),0x80);
  *(undefined1 *)(param_3 + 0x538) = 0;
  *(undefined1 *)(param_3 + 0x5b9) = 0;
  *(undefined1 *)(param_3 + 0x63a) = 0;
  *(undefined1 *)(param_3 + 0x6bb) = 0;
  __memzero((void *)(param_3 + 0x6bc),3);
  uVar17 = (uint)(byte)param_7[1];
  uVar12 = uVar17 + 2;
  do {
    if (__n < uVar12) {
      return;
    }
    cVar1 = *param_7;
    if (cVar1 == '6') {
      if (uVar17 == 3) {
        *(undefined1 *)(param_3 + 0x6bb) = 1;
        memmove((void *)(param_3 + 0x6bc),param_7 + 2,(uint)(byte)param_7[1]);
      }
    }
    else if (cVar1 == -0x23) {
      __s1 = param_7 + 2;
      iVar6 = memcmp(__s1,&WPS_OUI,4);
      if (iVar6 == 0) {
        *(byte *)(param_3 + 0x534) = *(byte *)(param_3 + 0x534) | 1;
        WscCheckWpsIeFromWpsAP(param_1,param_7,param_3 + 0x536);
        uVar17 = (byte)param_7[1] + 2;
        if (uVar17 < 0x81) {
          *(char *)(param_3 + 0x63a) = (char)uVar17;
          memmove((void *)(param_3 + 0x63b),param_7,uVar17 & 0xff);
        }
        else {
          *(undefined1 *)(param_3 + 0x63a) = 0;
        }
      }
      else {
        iVar6 = memcmp(__s1,&WPA_OUI,4);
        if (iVar6 == 0) {
          uVar17 = uVar17 + 2;
          if (0x80 < uVar17) {
            *(undefined1 *)(param_3 + 0x538) = 0;
            goto LAB_0010ede8;
          }
          *(char *)(param_3 + 0x538) = (char)uVar17;
          memmove((void *)(param_3 + 0x539),param_7,uVar17 & 0xff);
        }
        check_vendor_ie(param_1,param_7,param_4 + 200);
        if (*(char *)(param_4 + 0xd9) != '\0') {
          *(bool *)(param_3 + 0x6c2) = *(char *)(param_4 + 0xda) != '\0';
        }
        iVar6 = memcmp(__s1,&OWE_TRANS_OUI,4);
        if (iVar6 == 0) {
          __memzero((void *)(param_3 + 0x6c5),0x400);
          memmove((void *)(param_3 + 0x6c5),param_7 + 6,(byte)param_7[1] - 4);
          *(ushort *)(param_3 + 0xac6) = (byte)param_7[1] - 4;
        }
      }
    }
    else if ((cVar1 == '0') && (iVar6 = memcmp(param_7 + 4,&RSN_OUI,3), iVar6 == 0)) {
      uVar17 = uVar17 + 2;
      if (uVar17 < 0x81) {
        *(char *)(param_3 + 0x5b9) = (char)uVar17;
        memmove((void *)(param_3 + 0x5ba),param_7,uVar17 & 0xff);
      }
      else {
        *(undefined1 *)(param_3 + 0x5b9) = 0;
      }
    }
LAB_0010ede8:
    pbVar13 = (byte *)(param_7 + 1);
    param_7 = param_7 + *pbVar13 + 2;
    uVar16 = uVar16 + *pbVar13 + 2 & 0xffff;
    uVar17 = (uint)(byte)param_7[1];
    uVar12 = uVar16 + 2 + uVar17;
  } while( true );
LAB_0010eca8:
  if (*(int *)(param_3 + 0xc4) == 0) goto LAB_0010ecb4;
  goto LAB_0010ecf4;
}

