// module: mt7915.ko
// function: RTMPAR9IoctlGetMacTableNew @ 0x15c9dc
// size: 1676 bytes
//

void RTMPAR9IoctlGetMacTableNew(int param_1,int param_2)

{
  int *__s2;
  void *pvVar1;
  int iVar2;
  char *__src;
  int iVar3;
  uint uVar4;
  ushort uVar5;
  int *piVar6;
  uint uVar7;
  int iVar8;
  int *piVar9;
  char *pcVar10;
  int iVar11;
  void *pvVar12;
  int iVar13;
  char *pcVar14;
  int iVar15;
  int local_70;
  int *local_6c;
  int local_68;
  int local_64;
  int *local_60;
  int *local_5c;
  int local_58;
  int *local_54;
  uint local_50;
  void *local_4c;
  int local_48;
  void *local_44;
  int local_40;
  void *local_3c;
  int local_34;
  int local_30;
  int *local_2c [2];
  
  local_2c[0] = (int *)0x0;
  local_50 = (uint)*(ushort *)(param_2 + 0x16);
  local_34 = 0;
  local_30 = 0;
  local_70 = param_1;
  local_40 = param_2;
  os_alloc_mem(0,local_2c,0x9a04);
  if (local_2c[0] == (int *)0x0) {
    printk("%s: Allocate memory fail!!!\n","RTMPAR9IoctlGetMacTableNew");
  }
  else {
    __memzero(local_2c[0],0x9a04);
    iVar8 = 0;
    iVar13 = 0;
    local_44 = (void *)(local_70 + 0xa7dfbc);
    local_4c = (void *)(local_70 + 0xa86c5c);
    pcVar14 = (char *)(local_70 + 0xa31d9);
    pcVar10 = (char *)(local_70 + 0xa7dfb9);
    piVar9 = (int *)(local_70 + 0xa1d20);
    local_3c = (void *)(local_70 + 0xa7da38);
    local_48 = 0;
    local_58 = 0;
    *local_2c[0] = 0;
    do {
      if ((*piVar9 == 0x20001) && (iVar11 = local_70 + iVar8, *(int *)(iVar11 + 0xa1e1c) == 2)) {
        local_6c = local_2c[0];
        local_68 = *local_2c[0];
        if (0x7f < local_68) break;
        piVar6 = (int *)(local_70 + iVar8 + 0xa1e0c);
        local_54 = local_2c[0] + local_68 * 0x4d + 2;
        local_2c[0][local_68 * 0x4d + 2] = *piVar6;
        *(short *)(local_2c[0] + local_68 * 0x4d + 3) = (short)piVar6[1];
        local_2c[0][local_68 * 0x4d + 1] = (uint)*(byte *)(iVar11 + 0xa1e05);
        if (local_50 == 0) {
          ZTE_GetRealTimeTxRxRate(local_70,piVar9,&local_34,&local_30);
          if (2 < DebugLevel) {
            printk("TxDataRate=%lu RxDataRate=%lu\n",local_34,local_30);
          }
        }
        else {
          ZTE_GetAssocRate(piVar9,&local_34);
          local_30 = local_34;
        }
        local_64 = local_68 * 0x134;
        piVar6 = local_6c + local_68 * 0x4d;
        piVar6[10] = local_30 * 1000;
        piVar6[9] = local_34 * 1000;
        local_5c = piVar6;
        iVar2 = RTMPAvgRssi(local_70,local_70 + iVar8 + 0xa1e28);
        piVar6[6] = iVar2;
        iVar2 = MCSRate2Index(piVar9,*(undefined1 *)(iVar11 + 0xa1e54));
        piVar6[5] = iVar2;
        iVar15 = iVar13 * 0x14c0 + local_70;
        local_60 = (int *)((int)local_6c + local_64 + 0x2c);
        local_64 = iVar15;
        __src = (char *)get_phymode_str(*(byte *)(iVar15 + 0xa1ddd) >> 5);
        strncpy((char *)local_60,__src,0x13);
        iVar2 = local_68;
        piVar6 = local_6c;
        local_5c[4] = *(int *)(iVar11 + 0xa1d34);
        iVar3 = local_64 + 0xa1000;
        local_5c[0x1d] = *(int *)(iVar11 + 0xa3068);
        local_5c[0x1e] = *(int *)(iVar11 + 0xa3070);
        local_5c[0x11] = *(int *)(iVar11 + 0xa3020);
        local_5c[0x12] = *(int *)(iVar11 + 0xa3028);
        local_5c[0x16] = *(int *)(iVar11 + 0xa3030);
        local_5c[0x17] = *(int *)(iVar11 + 0xa3038);
        local_5c[0x15] = *(int *)(iVar11 + 0xa2824);
        local_5c[0x24] = *(int *)(iVar11 + 0xa3050);
        *(undefined1 *)(local_5c + 0x36) = *(undefined1 *)(iVar11 + 0xa2818);
        *(undefined1 *)(local_5c + 0x23) = *(undefined1 *)(iVar11 + 0xa2a42);
        *(bool *)((int)local_5c + 0x8d) = (*(byte *)(local_64 + 0xa2f0c) & 0x30) != 0;
        *(undefined1 *)(local_5c + 0x4b) = *(undefined1 *)(iVar11 + 0xa31d8);
        *(char *)((int)local_5c + 0x12d) = *pcVar14;
        if (*(byte *)(iVar15 + 0xa1ddd) < 0x80) {
          if ((*(byte *)(local_64 + 0xa1ddd) & 0xc0) == 0x40) {
            iVar15 = (((uint)*(byte *)(iVar15 + 0xa1ddc) << 0x1a) >> 0x1d) + 1;
          }
          else {
            iVar15 = 1;
          }
          local_5c[0x20] = iVar15;
        }
        else {
          local_5c[0x20] = (((uint)*(byte *)(iVar15 + 0xa1ddc) << 0x1a) >> 0x1e) + 1;
        }
        uVar5 = *(ushort *)(iVar13 * 0x14c0 + local_70 + 0xa1dde) & 0x180;
        if (uVar5 == 0x100) {
          local_6c[local_68 * 0x4d + 0x21] = 3;
        }
        else {
          local_6c[local_68 * 0x4d + 0x21] = (uint)(uVar5 == 0x80);
        }
        *(undefined1 *)(local_6c + local_68 * 0x4d + 0x4b) = *(undefined1 *)(iVar11 + 0xa31d8);
        local_64 = iVar3;
        if ((*(int *)(iVar11 + 0xa1d28) == 0) || (local_58 = HcGetBandByWdev(), local_58 != 1)) {
          pvVar1 = local_4c;
          piVar6 = local_54;
          if (*pcVar14 == '\x01') goto LAB_0015ceac;
          pvVar12 = local_44;
          local_4c = pvVar1;
          if (local_58 == 0) {
            do {
              if (((('\x04' < *(char *)((int)pvVar12 + -3)) && (*pcVar10 < '\n')) &&
                  (*(char *)((int)pvVar12 + -4) != '\0')) &&
                 (iVar11 = memcmp(pvVar12,piVar6,6), iVar11 == 0)) {
                local_48 = 1;
                *(undefined1 *)((int)local_6c + local_68 * 0x134 + 0x12d) = 1;
                *local_2c[0] = *local_2c[0] + 1;
                local_4c = pvVar1;
                goto LAB_0015caac;
              }
              __s2 = local_54;
              pvVar12 = (void *)((int)pvVar12 + 0x48);
            } while (pvVar12 != pvVar1);
            local_4c = pvVar1;
            if ((local_48 == 0) && (iVar11 = *(int *)(local_70 + 0xa7d9b4), iVar11 != 0)) {
              iVar2 = 0;
              pvVar12 = local_3c;
              local_64 = iVar8;
              local_60 = piVar9;
              do {
                iVar2 = iVar2 + 1;
                iVar3 = memcmp(pvVar12,__s2,6);
                pvVar12 = (void *)((int)pvVar12 + 6);
                iVar8 = local_64;
                piVar9 = local_60;
                if (iVar3 == 0) goto LAB_0015ceac;
              } while (iVar2 != iVar11);
              *local_2c[0] = *local_2c[0] + 1;
              local_4c = pvVar1;
              goto LAB_0015caac;
            }
          }
        }
        else {
          *(undefined1 *)((int)piVar6 + iVar2 * 0x134 + 0x12d) = 1;
          pvVar1 = local_4c;
          if (*pcVar14 != '\x01') {
            *local_2c[0] = *local_2c[0] + 1;
            goto LAB_0015caac;
          }
LAB_0015ceac:
          local_4c = pvVar1;
          *(undefined1 *)((int)local_6c + local_68 * 0x134 + 0x12d) = 1;
        }
        *local_2c[0] = *local_2c[0] + 1;
      }
LAB_0015caac:
      iVar8 = iVar8 + 0x14c0;
      iVar13 = iVar13 + 1;
      piVar9 = piVar9 + 0x530;
      pcVar14 = pcVar14 + 0x14c0;
      pcVar10 = pcVar10 + 0x48;
    } while (iVar8 != 0x175800);
    uVar4 = *(uint *)(local_40 + 0x10);
    uVar7 = *(uint *)(((uint)&local_70 & 0xffffe000) + 8);
    *(undefined2 *)(local_40 + 0x14) = 0x9a04;
    if (uVar4 < 0xffff65fc && uVar4 + 0x9a04 <= uVar7) {
      uVar7 = 0;
    }
    local_6c = local_2c[0];
    if ((uVar7 != 0) || (iVar8 = __copy_to_user(uVar4,local_2c[0]), iVar8 != 0)) {
      printk("%s: copy_to_user() fail\n","RTMPAR9IoctlGetMacTableNew");
    }
    os_free_mem(local_2c[0]);
  }
  return;
}

