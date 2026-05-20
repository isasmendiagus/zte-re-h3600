// module: mt7915.ko
// function: PaserSecurityIE @ 0x56aa4
// size: 1848 bytes
//

void PaserSecurityIE(int param_1,ushort *param_2,int param_3,uint *param_4,uint *param_5,
                    uint *param_6,undefined4 *param_7,short *param_8,undefined2 *param_9)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte *pbVar5;
  int iVar6;
  byte *pbVar7;
  byte *pbVar8;
  short sVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  int iVar15;
  byte local_29 [5];
  
  *param_4 = 0;
  *param_5 = 0;
  *param_6 = 0;
  uVar12 = (uint)*param_2;
  local_29[0] = 0;
  iVar10 = (int)(short)*param_2;
  uVar14 = uVar12;
  if (iVar10 < 1) {
LAB_00056d7c:
    if (*param_4 == 0) {
      *param_4 = 1;
      if ((*(ushort *)(param_1 + 0x34) & 0x10) != 0) {
        *param_4 = 3;
        *param_5 = *param_5 | 0xe;
        *param_6 = *param_6 | 0xe;
        return;
      }
      *param_5 = *param_5 | 1;
      *param_6 = *param_6 | 1;
    }
    return;
  }
  do {
    iVar15 = param_3 + (uVar12 - iVar10);
    cVar1 = *(char *)(param_3 + (uVar12 - iVar10));
    if (cVar1 == '0') {
      iVar10 = wpa_rsne_sanity(iVar15,*(char *)(iVar15 + 1) + '\x02',local_29);
      bVar4 = local_29[0];
      if (iVar10 == 0) goto LAB_00056ca8;
      if (local_29[0] == 0) {
        *param_6 = *param_6 | 0x20;
LAB_00056ce8:
        *param_5 = *param_5 | 0x20;
LAB_00056cf4:
        *param_4 = *param_4 | 0x40;
      }
      else {
        if (local_29[0] < 2) goto LAB_00056ce8;
        if (local_29[0] == 2) goto LAB_00056cf4;
      }
      if ((*(short *)(iVar15 + 2) != 1 || local_29[0] == 0) ||
         (iVar10 = memcmp((void *)(iVar15 + 4),&OUI_WPA2_CIPHER,3), iVar10 != 0)) goto LAB_00056ca8;
      switch(*(undefined1 *)(iVar15 + 7)) {
      case 1:
        *param_6 = *param_6 | 2;
        break;
      case 2:
        *param_6 = *param_6 | 0x10;
        break;
      case 4:
        *param_6 = *param_6 | 0x20;
        break;
      case 5:
        *param_6 = *param_6 | 4;
        break;
      case 8:
        *param_6 = *param_6 | 0x80;
        break;
      case 9:
        *param_6 = *param_6 | 0x100;
        break;
      case 10:
        *param_6 = *param_6 | 0x40;
      }
      if (bVar4 < 2) goto LAB_00056ca8;
      pbVar7 = (byte *)(iVar15 + 10);
      sVar9 = (ushort)*(byte *)(iVar15 + 8) + (ushort)*(byte *)(iVar15 + 9) * 0x100;
      if (sVar9 != 0) {
        pbVar5 = pbVar7 + ((ushort)(sVar9 - 1) + 1) * 4;
        pbVar8 = pbVar7;
        do {
          switch(pbVar8[3]) {
          case 1:
            *param_5 = *param_5 | 2;
            break;
          case 2:
            *param_5 = *param_5 | 0x10;
            break;
          case 4:
            *param_5 = *param_5 | 0x20;
            break;
          case 5:
            *param_5 = *param_5 | 4;
            break;
          case 8:
            *param_5 = *param_5 | 0x80;
            break;
          case 9:
            *param_5 = *param_5 | 0x100;
            break;
          case 10:
            *param_5 = *param_5 | 0x40;
          }
          pbVar8 = pbVar8 + 4;
          pbVar7 = pbVar5;
        } while (pbVar8 != pbVar5);
      }
      if (bVar4 == 2) goto LAB_00056ca8;
      pbVar8 = pbVar7 + 2;
      sVar9 = (ushort)*pbVar7 + (ushort)pbVar7[1] * 0x100;
      if (sVar9 != 0) {
        do {
          iVar10 = memcmp(pbVar8,&OUI_WPA2_CIPHER,3);
          if (iVar10 != 0) break;
          switch(pbVar8[3]) {
          case 0:
            *param_4 = *param_4 | 0x20;
            break;
          case 1:
            *param_4 = *param_4 | 0x40;
            break;
          case 2:
            *param_4 = *param_4 | 0x80;
            break;
          case 3:
            *param_4 = *param_4 | 0x100;
            break;
          case 4:
            *param_4 = *param_4 | 0x200;
            break;
          case 5:
            *param_4 = *param_4 | 0x40;
            *param_9 = 1;
            break;
          case 6:
            *param_4 = *param_4 | 0x80;
            *param_9 = 1;
            break;
          case 7:
            *param_4 = *param_4 | 0x1000;
            break;
          case 8:
            *param_4 = *param_4 | 0x2000;
            break;
          case 9:
            *param_4 = *param_4 | 0x4000;
            break;
          case 0xb:
            *param_4 = *param_4 | 0x8000;
            break;
          case 0xc:
            *param_4 = *param_4 | 0x10000;
            break;
          case 0xd:
            *param_4 = *param_4 | 0x20000;
            break;
          case 0x12:
            *param_4 = *param_4 | 0x100000;
          }
          pbVar8 = pbVar8 + 4;
        } while (pbVar8 != pbVar7 + (uint)(ushort)(sVar9 - 1) * 4 + 6);
      }
      if (*(char *)(param_1 + 0x2d) == '\0') {
        *param_4 = *param_4 | 0x20;
      }
      if (bVar4 == 3) goto LAB_00056ca8;
      sVar9 = (ushort)*pbVar8 + (ushort)pbVar8[1] * 0x100;
      *param_8 = sVar9;
      if (sVar9 == 0) {
LAB_0005709c:
        if (bVar4 != 4) {
          bVar2 = pbVar8[3];
          bVar3 = pbVar8[2];
          if (bVar4 != 5) goto LAB_000570b4;
        }
        goto LAB_00056ca8;
      }
      if (bVar4 < 6) {
        *param_7 = 0x200;
        goto LAB_0005709c;
      }
      bVar2 = pbVar8[3];
      bVar3 = pbVar8[2];
LAB_000570b4:
      iVar10 = memcmp(pbVar8 + ((uint)bVar3 + (uint)bVar2 * 0x100 & 0xffff) * 0x10 + 4,
                      &OUI_WPA2_CIPHER,3);
      if (iVar10 != 0) goto LAB_00056ca8;
      switch((pbVar8 + ((uint)bVar3 + (uint)bVar2 * 0x100 & 0xffff) * 0x10 + 4)[3]) {
      case 6:
        *param_7 = 0x200;
        uVar13 = (uint)*(byte *)(iVar15 + 1);
        break;
      default:
        if (-1 < DebugLevel) {
          printk("%s: unknown Group Management Cipher Suite %d\n","PaserSecurityIE");
        }
        goto LAB_00056ca8;
      case 0xb:
        *param_7 = 0x800;
        uVar13 = (uint)*(byte *)(iVar15 + 1);
        break;
      case 0xc:
        *param_7 = 0x1000;
        uVar13 = (uint)*(byte *)(iVar15 + 1);
        break;
      case 0xd:
        *param_7 = 0x400;
        uVar13 = (uint)*(byte *)(iVar15 + 1);
      }
    }
    else {
      if (cVar1 == -0x23) {
        iVar10 = memcmp((void *)(iVar15 + 2),&SES_OUI,3);
        if ((iVar10 == 0) && (uVar13 = (uint)*(byte *)(iVar15 + 1), uVar13 == 7)) goto LAB_00056c34;
        iVar10 = memcmp((void *)(iVar15 + 2),&OUI_WPA_VERSION,4);
        if (iVar10 == 0) {
          switch(*(undefined1 *)(iVar15 + 0xb)) {
          case 1:
            *param_6 = *param_6 | 2;
            break;
          case 2:
            *param_6 = *param_6 | 0x10;
            break;
          case 4:
            *param_6 = *param_6 | 0x20;
            break;
          case 5:
            *param_6 = *param_6 | 4;
          }
          iVar10 = iVar15 + 0xe;
          sVar9 = (ushort)*(byte *)(iVar15 + 0xc) + (ushort)*(byte *)(iVar15 + 0xd) * 0x100;
          if (sVar9 != 0) {
            iVar6 = iVar10 + ((ushort)(sVar9 - 1) + 1) * 4;
            iVar11 = iVar10;
            do {
              switch(*(undefined1 *)(iVar11 + 3)) {
              case 1:
                *param_5 = *param_5 | 2;
                break;
              case 2:
                *param_5 = *param_5 | 0x10;
                break;
              case 4:
                *param_5 = *param_5 | 0x20;
                break;
              case 5:
                *param_5 = *param_5 | 4;
              }
              iVar11 = iVar11 + 4;
              iVar10 = iVar6;
            } while (iVar11 != iVar6);
          }
          if (*(char *)(iVar10 + 5) == '\x01') {
            *param_4 = *param_4 | 8;
          }
          else if (*(char *)(iVar10 + 5) == '\x02') {
            *param_4 = *param_4 | 0x10;
          }
          if (*(char *)(param_1 + 0x2d) == '\0') {
            *param_4 = *param_4 | 0x20;
            uVar13 = (uint)*(byte *)(iVar15 + 1);
            goto LAB_00056c34;
          }
        }
      }
LAB_00056ca8:
      uVar13 = (uint)*(byte *)(iVar15 + 1);
    }
LAB_00056c34:
    uVar13 = (uVar14 - 2) - uVar13;
    iVar10 = (int)(short)uVar13;
    if (iVar10 < 1) goto LAB_00056d7c;
    uVar12 = (uint)*param_2;
    uVar14 = uVar13 & 0xffff;
  } while( true );
}

