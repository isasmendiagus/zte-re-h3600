// module: mt7915.ko
// function: RTMPIoctlE2PROM @ 0x60b68
// size: 2324 bytes
//

void RTMPIoctlE2PROM(int param_1,int param_2)

{
  byte *__s;
  undefined1 *puVar1;
  size_t sVar2;
  size_t sVar3;
  byte *pbVar4;
  uint uVar5;
  byte *pbVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  undefined2 *puVar11;
  undefined2 *puVar12;
  char *pcVar13;
  undefined2 *puVar14;
  undefined2 *puVar15;
  char *pcVar16;
  undefined1 auStack_58 [2];
  undefined2 local_56;
  char *local_54;
  byte *local_50;
  uint local_4c;
  byte local_48;
  byte local_47;
  undefined4 local_38;
  byte local_34 [16];
  
  local_54 = (char *)0x0;
  local_50 = (byte *)0x0;
  os_alloc_mem(0,&local_54,0x400);
  if (local_54 == (char *)0x0) {
    if (DebugLevel < 0) goto LAB_00060ca4;
LAB_00060d00:
    printk("%s: Allocate memory fail!!!\n","RTMPIoctlE2PROM");
    pcVar16 = local_54;
    goto LAB_00060c94;
  }
  os_alloc_mem(0,&local_50,0xff);
  if (local_50 != (byte *)0x0) {
    __memzero(local_54,0x400);
    __memzero(local_50,0xff);
    uVar5 = (uint)*(ushort *)(param_2 + 0x14);
    if (uVar5 < 2) {
LAB_00060d18:
      os_alloc_mem(0,&local_38,0x100);
      puVar15 = local_38;
      if (local_38 != (undefined2 *)0x0) {
        puVar14 = local_38 + 0x80;
        puVar11 = local_38;
        do {
          chip_eeprom_read16(param_1,(int)puVar11 - (int)puVar15,&local_4c);
          puVar12 = puVar11 + 1;
          *puVar11 = (undefined2)local_4c;
          puVar11 = puVar12;
        } while (puVar12 != puVar14);
        RtmpDrvAllE2PPrint(param_1,local_38,0xfe,2);
        os_free_mem(local_38);
        goto LAB_00060c50;
      }
      goto LAB_00061148;
    }
    if (0xfe < uVar5) {
      uVar5 = 0xff;
    }
    uVar8 = *(uint *)(((uint)auStack_58 & 0xffffe000) + 8);
    if (!CARRY4(*(uint *)(param_2 + 0x10),uVar5) && *(uint *)(param_2 + 0x10) + uVar5 <= uVar8) {
      uVar8 = 0;
    }
    if (uVar8 == 0) {
      __copy_from_user(local_50);
    }
    else {
      __memzero(local_50,uVar5);
    }
    __s = local_50;
    local_54[0] = '\n';
    local_54[1] = '\0';
    local_50[0xfe] = 0;
    if (*local_50 != 0) {
      puVar1 = (undefined1 *)rtstrchr(local_50,0x3d);
      if (puVar1 == (undefined1 *)0x0) {
        puVar1 = (undefined1 *)rtstrchr(__s,0x2d);
        pcVar16 = local_54;
        if (puVar1 == (undefined1 *)0x0) goto LAB_00060dbc;
        *puVar1 = 0;
        pcVar13 = puVar1 + 1;
        sVar2 = strlen(local_54);
        builtin_strncpy(pcVar16 + sVar2,"printing range e2p value\n",0x1a);
        sVar2 = strlen(pcVar13);
        memcpy(&local_38,pcVar13,sVar2);
        sVar2 = strlen(pcVar13);
        local_34[sVar2 - 4] = 0;
        sVar2 = strlen((char *)__s);
        if ((sVar2 < 5) && (sVar3 = strlen((char *)&local_38), sVar3 < 5)) {
          pcVar16 = local_54;
          if (sVar2 == 0) {
            if (sVar3 == 0) {
              sVar2 = 0;
              goto LAB_000612cc;
            }
LAB_00061268:
            if (((uint)local_38 & 0xff) - 0x30 < 0x37) {
              uVar5 = 0;
              pbVar6 = (byte *)&local_38;
              do {
                uVar5 = uVar5 + 1;
                if (sVar3 <= uVar5) goto LAB_000612a0;
                pbVar6 = pbVar6 + 1;
              } while (*pbVar6 - 0x30 < 0x37);
            }
          }
          else if (*__s - 0x30 < 0x37) {
            pbVar6 = __s;
            do {
              pbVar6 = pbVar6 + 1;
              if (pbVar6 == __s + sVar2) {
                if (sVar3 != 0) goto LAB_00061268;
                goto LAB_000612a0;
              }
            } while (*pbVar6 - 0x30 < 0x37);
          }
          goto LAB_00060c94;
        }
      }
      else {
        pcVar16 = puVar1 + 1;
        *puVar1 = 0;
        if ((pcVar16 != (char *)0x0) && (puVar1[1] != '\0')) {
          sVar2 = strlen(pcVar16);
          memcpy(&local_38,pcVar16,sVar2);
          sVar2 = strlen(pcVar16);
          local_34[sVar2 - 4] = 0;
          sVar2 = strlen((char *)__s);
          if ((4 < sVar2) || (sVar3 = strlen((char *)&local_38), 8 < sVar3)) goto LAB_00060c50;
          pcVar16 = local_54;
          if (sVar2 == 0) {
            if (sVar3 == 0) {
              sVar2 = 0;
              goto LAB_00061020;
            }
LAB_00060fbc:
            if (((uint)local_38 & 0xff) - 0x30 < 0x37) {
              uVar5 = 0;
              pbVar6 = (byte *)&local_38;
              do {
                uVar5 = uVar5 + 1;
                if (sVar3 <= uVar5) goto LAB_00060ff4;
                pbVar6 = pbVar6 + 1;
              } while (*pbVar6 - 0x30 < 0x37);
            }
          }
          else if (*__s - 0x30 < 0x37) {
            pbVar6 = __s;
            do {
              pbVar6 = pbVar6 + 1;
              if (pbVar6 == __s + sVar2) {
                if (sVar3 != 0) goto LAB_00060fbc;
                goto LAB_00060ff4;
              }
            } while (*pbVar6 - 0x30 < 0x37);
          }
          goto LAB_00060c94;
        }
LAB_00060dbc:
        sVar2 = strlen((char *)__s);
        if (sVar2 < 5) {
          if (sVar2 != 0) {
            pcVar16 = local_54;
            if (*__s - 0x30 < 0x37) {
              pbVar4 = __s + sVar2;
              pbVar6 = __s;
LAB_00060e00:
              pbVar6 = pbVar6 + 1;
              if (pbVar6 != pbVar4) goto LAB_00060df0;
              pbVar6 = __s + 4;
              do {
                pbVar4 = pbVar4 + -1;
                pbVar6 = pbVar6 + -1;
                *pbVar6 = *pbVar4;
              } while (pbVar4 != __s);
              if (sVar2 != 4) goto LAB_00060e24;
              goto LAB_00060e40;
            }
            goto LAB_00060c94;
          }
LAB_00060e24:
          pbVar6 = __s + (3 - sVar2);
          do {
            pbVar4 = pbVar6 + -1;
            *pbVar6 = 0x30;
            pbVar6 = pbVar4;
          } while (pbVar4 != __s + -1);
LAB_00060e40:
          __s[4] = 0;
          sVar2 = strlen((char *)__s);
          if (sVar2 == 4) {
            AtoH(__s,&local_48,2);
            uVar5 = (uint)local_47 + (uint)local_48 * 0x100 & 0xffff;
            if (uVar5 == 0xffff) goto LAB_00060d18;
            chip_eeprom_read16(param_1,uVar5,&local_4c);
            pcVar16 = local_54;
            sVar2 = strlen(local_54);
            sprintf(pcVar16 + sVar2,"[0x%04X]:0x%04X  ",uVar5,local_4c & 0xffff);
          }
        }
      }
    }
    goto LAB_00060c50;
  }
  if (-1 < DebugLevel) goto LAB_00060d00;
  pcVar16 = local_54;
  if (local_54 == (char *)0x0) {
    return;
  }
  goto LAB_00060c9c;
LAB_000612a0:
  if (sVar2 == 0) {
LAB_000612cc:
    pbVar6 = __s + (3 - sVar2);
    do {
      pbVar4 = pbVar6 + -1;
      *pbVar6 = 0x30;
      pbVar6 = pbVar4;
    } while (pbVar4 != __s + -1);
  }
  else {
    pbVar4 = __s + sVar2;
    pbVar6 = __s + 4;
    do {
      pbVar4 = pbVar4 + -1;
      pbVar6 = pbVar6 + -1;
      *pbVar6 = *pbVar4;
    } while (pbVar4 != __s);
    if (sVar2 != 4) goto LAB_000612cc;
  }
  __s[4] = 0;
  sVar2 = strlen((char *)&local_38);
  iVar10 = sVar2 - 1;
  if (-1 < iVar10) {
    pbVar6 = (byte *)((int)&local_38 + sVar2);
    pbVar4 = local_34;
    do {
      iVar10 = iVar10 + -1;
      pbVar6 = pbVar6 + -1;
      pbVar4 = pbVar4 + -1;
      *pbVar4 = *pbVar6;
    } while (iVar10 != -1);
  }
  if ((int)sVar2 < 4) {
    pbVar6 = (byte *)((int)&local_38 + (4 - sVar2));
    do {
      pbVar6 = pbVar6 + -1;
      *pbVar6 = 0x30;
    } while (pbVar6 != (byte *)&local_38);
  }
  local_34[0] = 0;
  AtoH(__s,&local_48,2);
  uVar8 = (uint)local_48;
  uVar5 = (uint)local_47;
  AtoH(&local_38,&local_48,2);
  pcVar16 = local_54;
  uVar5 = uVar5 + uVar8 * 0x100 & 0xffff;
  uVar8 = (uint)local_47 + (uint)local_48 * 0x100 & 0xffff;
  if (uVar5 < uVar8) {
    os_alloc_mem(0,&local_4c,uVar8 - uVar5);
    if (local_4c == 0) {
LAB_00061148:
      if (2 < DebugLevel) {
        printk("-->2) %s: Allocate memory fail!\n","RTMPIoctlE2PROM");
      }
    }
    else {
      puVar15 = (undefined2 *)(local_4c - 2);
      do {
        chip_eeprom_read16(param_1,uVar5,&local_56);
        puVar15 = puVar15 + 1;
        *puVar15 = local_56;
        if (2 < DebugLevel) {
          printk("eepAddr=%08x, eepValue=%04x\n",uVar5,local_56);
        }
        uVar5 = uVar5 + 2 & 0xffff;
      } while (uVar5 <= uVar8);
      os_free_mem(local_4c);
    }
  }
  else {
    sVar2 = strlen(local_54);
    builtin_strncpy(pcVar16 + sVar2,"wrong input range!\n",0x14);
  }
  goto LAB_00060c50;
LAB_00060df0:
  if (0x36 < *pbVar6 - 0x30) goto LAB_00060c94;
  goto LAB_00060e00;
LAB_00060ff4:
  if (sVar2 == 0) {
LAB_00061020:
    pbVar6 = __s + (3 - sVar2);
    do {
      pbVar4 = pbVar6 + -1;
      *pbVar6 = 0x30;
      pbVar6 = pbVar4;
    } while (pbVar4 != __s + -1);
  }
  else {
    pbVar4 = __s + sVar2;
    pbVar6 = __s + 4;
    do {
      pbVar4 = pbVar4 + -1;
      pbVar6 = pbVar6 + -1;
      *pbVar6 = *pbVar4;
    } while (pbVar4 != __s);
    if (sVar2 != 4) goto LAB_00061020;
  }
  __s[4] = 0;
  sVar2 = strlen((char *)&local_38);
  iVar10 = sVar2 - 1;
  if (-1 < iVar10) {
    iVar7 = iVar10 + (4 - sVar2);
    if (-1 < iVar7) {
      pbVar4 = (byte *)((int)&local_38 + sVar2);
      pbVar6 = (byte *)((int)&local_38 + iVar7);
      do {
        iVar10 = iVar10 + -1;
        pbVar4 = pbVar4 + -1;
        *pbVar6 = *pbVar4;
        if (iVar10 == -1) break;
        pbVar6 = pbVar6 + -1;
      } while (-1 < (int)((4 - sVar2) + iVar10));
    }
  }
  if ((int)sVar2 < 4) {
    pbVar6 = (byte *)((int)&local_38 + (4 - sVar2));
    do {
      pbVar6 = pbVar6 + -1;
      *pbVar6 = 0x30;
    } while (pbVar6 != (byte *)&local_38);
  }
  local_34[0] = 0;
  AtoH(__s,&local_48,2);
  uVar8 = (uint)local_48;
  uVar5 = (uint)local_47;
  AtoH(&local_38,&local_48,2);
  uVar5 = uVar5 + uVar8 * 0x100 & 0xffff;
  local_4c = CONCAT22(local_4c._2_2_,(ushort)local_47 + (ushort)local_48 * 0x100);
  iVar10 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar10 + 0xc) != (code *)0x0) {
    (**(code **)(iVar10 + 0xc))(param_1,uVar5,local_4c & 0xffff);
  }
  pcVar16 = local_54;
  sVar2 = strlen(local_54);
  sprintf(pcVar16 + sVar2,"[0x%02X]:%02X  ",uVar5,local_4c & 0xffff);
LAB_00060c50:
  pcVar16 = local_54;
  uVar5 = strlen(local_54);
  pcVar13 = local_54;
  if (uVar5 == 1) {
    builtin_strncpy(pcVar16 + 1,"===>Error command format!",0x1a);
    uVar5 = strlen(local_54);
    pcVar16 = pcVar13;
  }
  *(short *)(param_2 + 0x14) = (short)uVar5;
  uVar8 = *(uint *)(param_2 + 0x10);
  uVar9 = *(uint *)(((uint)auStack_58 & 0xffffe000) + 8);
  if (!CARRY4(uVar8,uVar5 & 0xffff) && uVar8 + (uVar5 & 0xffff) <= uVar9) {
    uVar9 = 0;
  }
  if (uVar9 == 0) {
    __copy_to_user(uVar8,pcVar16);
    pcVar16 = local_54;
  }
LAB_00060c94:
  if (pcVar16 != (char *)0x0) {
LAB_00060c9c:
    os_free_mem(pcVar16);
  }
LAB_00060ca4:
  if (local_50 != (byte *)0x0) {
    os_free_mem();
  }
  if (2 < DebugLevel) {
    printk("<==RTMPIoctlE2PROM\n");
  }
  return;
}

