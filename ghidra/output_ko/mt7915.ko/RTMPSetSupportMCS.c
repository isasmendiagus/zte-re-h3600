// module: mt7915.ko
// function: RTMPSetSupportMCS @ 0x1da358
// size: 1500 bytes
//

void RTMPSetSupportMCS(int param_1,int param_2,int *param_3,byte *param_4,char param_5,int param_6,
                      int param_7,char param_8)

{
  char cVar1;
  byte bVar2;
  ushort uVar3;
  byte *pbVar4;
  ushort *puVar6;
  uint uVar7;
  uint uVar8;
  uint __n;
  char *pcVar9;
  bool bVar10;
  undefined4 local_3c;
  undefined4 uStack_38;
  byte abStack_34 [16];
  byte *pbVar5;
  
  uVar7 = (uint)*param_4;
  __n = (uint)param_4[0xd];
  uVar8 = uVar7;
  if (uVar7 != 0) {
    if (uVar7 < 0xd) {
      os_move_mem(abStack_34,param_4 + 1,uVar7);
    }
    else {
      local_3c = 0x968b8482;
      uStack_38 = 0x6c482412;
      os_move_mem(abStack_34,&local_3c,8);
      if (2 < DebugLevel) {
        printk("%s():wrong SUPP RATES., Len=%d\n","RTMPSetSupportMCS",8);
      }
      uVar7 = 8;
      uVar8 = 0;
    }
  }
  if (__n == 0) {
LAB_001da408:
    *(undefined2 *)(param_3 + 0x302) = 0;
    *(undefined1 *)((int)param_3 + 0xbff) = 0;
    *(undefined1 *)(param_3 + 0x300) = 0;
    param_3[0x301] = 0;
    *(undefined1 *)((int)param_3 + 0xbfe) = 0;
    *(undefined2 *)((int)param_3 + 0xc0a) = 0;
    *(undefined2 *)(param_3 + 0x303) = 0;
    *(undefined2 *)((int)param_3 + 0xc0e) = 0;
    if (uVar8 != 0) goto LAB_001da448;
  }
  else {
    if (uVar7 + __n < 0xd) {
      os_move_mem(abStack_34 + uVar7,param_4 + 0xe,__n);
      uVar8 = uVar8 + __n & 0xff;
      goto LAB_001da408;
    }
    os_move_mem(abStack_34 + uVar7,param_4 + 0xe,0xc - __n);
    uVar8 = 0xc;
    *(undefined2 *)(param_3 + 0x302) = 0;
    *(undefined1 *)((int)param_3 + 0xbff) = 0;
    *(undefined1 *)(param_3 + 0x300) = 0;
    param_3[0x301] = 0;
    *(undefined1 *)((int)param_3 + 0xbfe) = 0;
    *(undefined2 *)((int)param_3 + 0xc0a) = 0;
    *(undefined2 *)(param_3 + 0x303) = 0;
    *(undefined2 *)((int)param_3 + 0xc0e) = 0;
LAB_001da448:
    pbVar5 = abStack_34;
    do {
      while( true ) {
        pbVar4 = pbVar5 + 1;
        uVar7 = (*pbVar5 & 0x7f) * 5;
        pbVar5 = pbVar4;
        if (uVar7 != 0x6e) break;
        *(byte *)((int)param_3 + 0xbff) = *(byte *)((int)param_3 + 0xbff) | 8;
        *(byte *)((int)param_3 + 0xbfe) = *(byte *)((int)param_3 + 0xbfe) | 1;
LAB_001da48c:
        if (uVar8 <= ((int)pbVar4 - (int)abStack_34 & 0xffU)) goto LAB_001da4f8;
      }
      if (0x6e < uVar7) {
        if (uVar7 == 0xf0) {
          *(byte *)(param_3 + 0x300) = *(byte *)(param_3 + 0x300) | 0x10;
          *(byte *)((int)param_3 + 0xbfe) = *(byte *)((int)param_3 + 0xbfe) | 2;
        }
        else if (uVar7 < 0xf1) {
          if (uVar7 == 0x78) {
            *(byte *)(param_3 + 0x300) = *(byte *)(param_3 + 0x300) | 4;
            *(byte *)((int)param_3 + 0xbfe) = *(byte *)((int)param_3 + 0xbfe) | 2;
          }
          else if (uVar7 == 0xb4) {
            *(byte *)(param_3 + 0x300) = *(byte *)(param_3 + 0x300) | 8;
            *(byte *)((int)param_3 + 0xbfe) = *(byte *)((int)param_3 + 0xbfe) | 2;
          }
        }
        else if (uVar7 == 0x1e0) {
          *(byte *)(param_3 + 0x300) = *(byte *)(param_3 + 0x300) | 0x40;
          *(byte *)((int)param_3 + 0xbfe) = *(byte *)((int)param_3 + 0xbfe) | 2;
        }
        else if (uVar7 == 0x21c) {
          *(byte *)((int)param_3 + 0xbfe) = *(byte *)((int)param_3 + 0xbfe) | 2;
          *(byte *)(param_3 + 0x300) =
               ~((byte)~(byte)(((uint)*(byte *)(param_3 + 0x300) << 0x19) >> 0x18) >> 1);
        }
        else if (uVar7 == 0x168) {
          *(byte *)(param_3 + 0x300) = *(byte *)(param_3 + 0x300) | 0x20;
          *(byte *)((int)param_3 + 0xbfe) = *(byte *)((int)param_3 + 0xbfe) | 2;
        }
        goto LAB_001da48c;
      }
      if (uVar7 == 0x37) {
        *(byte *)((int)param_3 + 0xbff) = *(byte *)((int)param_3 + 0xbff) | 4;
        *(byte *)((int)param_3 + 0xbfe) = *(byte *)((int)param_3 + 0xbfe) | 1;
        goto LAB_001da48c;
      }
      if (0x37 < uVar7) {
        if (uVar7 == 0x3c) {
          *(byte *)(param_3 + 0x300) = *(byte *)(param_3 + 0x300) | 1;
          *(byte *)((int)param_3 + 0xbfe) = *(byte *)((int)param_3 + 0xbfe) | 2;
        }
        else if (uVar7 == 0x5a) {
          *(byte *)(param_3 + 0x300) = *(byte *)(param_3 + 0x300) | 2;
          *(byte *)((int)param_3 + 0xbfe) = *(byte *)((int)param_3 + 0xbfe) | 2;
        }
        goto LAB_001da48c;
      }
      if (uVar7 == 10) {
        *(byte *)((int)param_3 + 0xbff) = *(byte *)((int)param_3 + 0xbff) | 1;
        *(byte *)((int)param_3 + 0xbfe) = *(byte *)((int)param_3 + 0xbfe) | 1;
        goto LAB_001da48c;
      }
      if (uVar7 != 0x14) goto LAB_001da48c;
      *(byte *)((int)param_3 + 0xbfe) = *(byte *)((int)param_3 + 0xbfe) | 1;
      *(byte *)((int)param_3 + 0xbff) = *(byte *)((int)param_3 + 0xbff) | 2;
    } while (((int)pbVar4 - (int)abStack_34 & 0xffU) < uVar8);
  }
LAB_001da4f8:
  if (param_8 == '\0') {
    return;
  }
  if (param_2 != 0) {
    if (param_2 != 1) {
      return;
    }
    if (*param_3 != 2 && *param_3 != 0x40001) {
      pcVar9 = "%s: per %u.\n" + (uint)*(byte *)(param_3 + 0x39) * 0x5834 + param_1 + 1;
      goto LAB_001da514;
    }
  }
  pcVar9 = (char *)(param_3[2] + 0x891);
LAB_001da514:
  if (pcVar9 != (char *)0x0) {
    uVar8 = 0x1f;
    do {
      cVar1 = (char)uVar8 >> 3;
      uVar7 = 1 << ((short)cVar1 * -8 + uVar8 & 0xff) & 0xff;
      if (((uVar7 & (byte)pcVar9[cVar1 + 2]) != 0) &&
         ((uVar7 & *(byte *)(param_7 + cVar1 + 3)) != 0)) {
        param_3[0x301] = param_3[0x301] | 1 << (uVar8 & 0xff);
        *(byte *)((int)param_3 + 0xbfe) = *(byte *)((int)param_3 + 0xbfe) | 4;
      }
      bVar10 = uVar8 != 0;
      uVar8 = uVar8 - 1;
    } while (bVar10);
    if (((param_5 != '\0' && param_6 != 0) && (pcVar9[0x12] != '\0')) &&
       (uVar8 = wlan_operate_get_tx_stream(param_3[2]), uVar8 != 0)) {
LAB_001da798:
      uVar8 = uVar8 - 1 & 0xff;
      switch(uVar8 + 1 & 0xff) {
      case 1:
        if ((*(byte *)(param_6 + 4) & 3) == 3) {
          return;
        }
        uVar3 = *(ushort *)(param_3 + 0x302);
        *(ushort *)(param_3 + 0x302) = uVar3 | 0xff;
        bVar2 = *(byte *)(param_6 + 4) & 3;
        if (bVar2 == 1) {
          *(ushort *)(param_3 + 0x302) = uVar3 | 0x1ff;
        }
        else if (bVar2 == 2) {
          *(ushort *)(param_3 + 0x302) = uVar3 | 0x3ff;
        }
        *(byte *)((int)param_3 + 0xbfe) = *(byte *)((int)param_3 + 0xbfe) | 8;
        return;
      case 2:
        if (((uint)*(byte *)(param_6 + 4) << 0x1c) >> 0x1e == 3) goto LAB_001da798;
        puVar6 = (ushort *)((int)param_3 + 0xc0a);
        uVar3 = *puVar6 | 0xff;
        *puVar6 = uVar3;
        bVar2 = *(byte *)(param_6 + 4) & 0xc;
        if (bVar2 == 4) {
LAB_001da920:
          *puVar6 = uVar3 | 0x100;
        }
        else if (bVar2 == 8) {
LAB_001da860:
          *puVar6 = uVar3 | 0x300;
        }
        break;
      case 3:
        if (((uint)*(byte *)(param_6 + 4) << 0x1a) >> 0x1e == 3) goto LAB_001da798;
        puVar6 = (ushort *)(param_3 + 0x303);
        uVar3 = *puVar6 | 0xff;
        *puVar6 = uVar3;
        bVar2 = *(byte *)(param_6 + 4) & 0x30;
        if (bVar2 == 0x10) goto LAB_001da920;
        if (bVar2 == 0x20) goto LAB_001da860;
        break;
      case 4:
        if (*(byte *)(param_6 + 4) >> 6 == 3) goto LAB_001da798;
        puVar6 = (ushort *)((int)param_3 + 0xc0e);
        uVar3 = *puVar6 | 0xff;
        *puVar6 = uVar3;
        bVar2 = *(byte *)(param_6 + 4) & 0xc0;
        if (bVar2 == 0x40) goto LAB_001da920;
        if (bVar2 == 0x80) goto LAB_001da860;
        break;
      default:
        goto LAB_001da914;
      }
      *(byte *)((int)param_3 + 0xbfe) = *(byte *)((int)param_3 + 0xbfe) | 8;
      goto LAB_001da798;
    }
  }
  return;
LAB_001da914:
  if (uVar8 == 0) {
    return;
  }
  goto LAB_001da798;
}

