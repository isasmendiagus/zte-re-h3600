// module: mt7915.ko
// function: traversal_func_dump_entry_associated_to_bss @ 0x14c09c
// size: 1992 bytes
//

undefined4 traversal_func_dump_entry_associated_to_bss(int param_1,uint *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  size_t sVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  undefined4 local_94;
  undefined4 local_90;
  char acStack_8a [30];
  undefined1 auStack_6c [49];
  byte local_3b;
  byte local_39;
  char local_38;
  byte local_37;
  char local_36;
  byte local_35;
  byte local_34;
  
  iVar8 = *(int *)(param_1 + 0xc);
  local_94 = 0;
  local_90 = 0;
  iVar1 = hc_get_chip_cap(*(undefined4 *)(iVar8 + 0xa797a0));
  if (param_2[1] != 0) {
    if ((0 < DebugLevel) &&
       (printk("Dump the entries associated to BssIDX:%d\n",*param_2), 0 < DebugLevel)) {
      printk("\n%-19s%-7s%-4s%-4s%-20s%-12s%-9s%-12s%-9s%-10s%-10s\n",&_LC76,&_LC77,&_LC78,&_LC79,
             "RSSI0/1/2/3","PhMd(T/R)","BW(T/R)","MCS(T/R)","SGI(T/R)","STBC(T/R)","Rate(T/R)");
    }
    param_2[1] = 0;
  }
  if (*param_2 != (uint)*(byte *)(param_1 + 0xe4)) {
    return 0;
  }
  local_94 = 0;
  getRate(*(undefined2 *)(param_1 + 0xbc),&local_94);
  if ((((0 < DebugLevel) &&
       (printk("%02x:%02x:%02x:%02x:%02x:%02x  ",*(undefined1 *)(param_1 + 0xec),
               *(undefined1 *)(param_1 + 0xed),*(undefined1 *)(param_1 + 0xee),
               *(undefined1 *)(param_1 + 0xef),*(undefined1 *)(param_1 + 0xf0),
               *(undefined1 *)(param_1 + 0xf1)), 0 < DebugLevel)) &&
      (printk(&_LC88,*(undefined2 *)(param_1 + 0xe0)), 0 < DebugLevel)) &&
     (printk(&_LC89,*(undefined1 *)(param_1 + 0xe4)), 0 < DebugLevel)) {
    printk(&_LC89,*(undefined1 *)(param_1 + 0xaf8));
  }
  iVar15 = (int)*(char *)(param_1 + 0x10d);
  iVar6 = (int)*(char *)(param_1 + 0x10e);
  iVar13 = (int)*(char *)(param_1 + 0x10f);
  snprintf(acStack_8a,0x1e,"%d/%d/%d/%d",(int)*(char *)(param_1 + 0x10c),iVar15,iVar6,iVar13);
  if (DebugLevel < 1) {
    if (*(char *)(iVar1 + 0x150) == '\x01') {
LAB_0014c27c:
      if (*(char *)(param_1 + 0xb7e) == '\x01') {
        uVar9 = *(uint *)(param_1 + 0x138);
        MtCmdGetTxStatistic(iVar8,4,0,*(undefined2 *)(param_1 + 0xe0),auStack_6c);
        uVar7 = (local_3b & 7) << 0xd | (local_37 & 3) << 7 | (uint)(local_36 != '\0') << 6 |
                (uint)(local_38 != '\0') << 9 | (local_39 & 1) << 10;
        if ((local_3b & 7) < 4) {
          if (((uVar7 << 0x10) >> 0x18 & 0xe0) == 0x20) {
            uVar10 = getLegacyOFDMMCSIndex(local_35);
            uVar7 = uVar7 | uVar10 & 0x3f;
          }
          else {
            uVar7 = uVar7 | local_35 & 0x3f;
          }
        }
        else {
          uVar7 = uVar7 | (uint)local_35 + (local_34 - 1 & 3) * 0x10 & 0x3f;
        }
        uVar11 = (uVar9 << 0x10) >> 0x1d;
        uVar2 = get_phymode_str(uVar7 >> 0xd);
        uVar3 = get_phymode_str(uVar11);
        uVar14 = uVar9 << 0x16;
        snprintf(acStack_8a,0x1e,"%s/%s",uVar2,uVar3);
        uVar10 = uVar9 << 0x15;
        if (0 < DebugLevel) {
          printk("%-12s",acStack_8a);
        }
        uVar2 = get_bw_str((uVar7 << 0x17) >> 0x1e);
        uVar4 = get_bw_str((uVar9 << 0x17) >> 0x1e);
        snprintf(acStack_8a,0x1e,"%s/%s",uVar2,uVar4);
        if (0 < DebugLevel) {
          printk(&_LC94,acStack_8a);
        }
        if (uVar7 >> 0xd < 4) {
          snprintf(acStack_8a,0x1e,"%d/",uVar7 & 0x3f,uVar4);
        }
        else {
          uVar4 = uVar7 & 0xf;
          snprintf(acStack_8a,0x1e,"%dS-M%d/",((uVar7 << 0x1a) >> 0x1e) + 1,uVar4);
        }
        if (uVar11 < 4) {
          uVar12 = uVar9 & 0x3f;
          if (uVar11 < 2) {
            if (uVar11 == 1) {
              if (uVar12 == 0xb) goto LAB_0014c4a4;
              if (uVar12 == 0xf) {
                uVar9 = uVar9 & 0xffffffc0 | 1;
              }
              else {
                if (uVar12 == 10) goto LAB_0014c804;
                if (uVar12 == 0xe) goto LAB_0014c81c;
                if (uVar12 == 9) {
                  uVar9 = uVar9 & 0xffffffc0 | 4;
                }
                else if (uVar12 == 0xd) {
                  uVar9 = uVar9 & 0xffffffc0 | 5;
                }
                else if (uVar12 == 8) {
                  uVar9 = uVar9 & 0xffffffc0 | 6;
                }
                else {
                  if (uVar12 != 0xc) goto LAB_0014c4a4;
                  uVar9 = uVar9 & 0xffffffc0 | 7;
                }
              }
            }
            else if (uVar12 == 0) {
LAB_0014c4a4:
              uVar9 = uVar9 & 0xffffffc0;
            }
            else if (uVar12 == 1) {
LAB_0014c810:
              uVar9 = uVar9 & 0xffffffc0 | 1;
            }
            else {
              if (uVar12 == 2) {
LAB_0014c804:
                uVar9 = uVar9 & 0xffffffc0 | 2;
                goto LAB_0014c4a8;
              }
              if (uVar12 != 3) {
                if (uVar12 == 5) goto LAB_0014c810;
                if (uVar12 == 6) goto LAB_0014c804;
                if (uVar12 != 7) goto LAB_0014c4a4;
              }
LAB_0014c81c:
              uVar9 = uVar9 & 0xffffffc0 | 3;
            }
LAB_0014c4a8:
            sVar5 = strlen(acStack_8a);
            snprintf(acStack_8a + sVar5,0x1e - sVar5,"%d",uVar9 & 0x3f,uVar4);
          }
          else {
            sVar5 = strlen(acStack_8a);
            snprintf(acStack_8a + sVar5,0x1e - sVar5,"%d",uVar12,uVar4);
          }
        }
        else {
          sVar5 = strlen(acStack_8a);
          snprintf(acStack_8a + sVar5,0x1e - sVar5,"%dS-M%d",((uVar9 << 0x1a) >> 0x1e) + 1,
                   uVar9 & 0xf);
        }
        if (0 < DebugLevel) {
          printk("%-12s",acStack_8a);
        }
        snprintf(acStack_8a,0x1e,"%d/%d",(uVar7 << 0x16) >> 0x1f,uVar14 >> 0x1f);
        if (0 < DebugLevel) {
          printk(&_LC94,acStack_8a);
        }
        snprintf(acStack_8a,0x1e,"%d/%d",(uVar7 << 0x15) >> 0x1f,uVar10 >> 0x1f);
        if (0 < DebugLevel) {
          printk("%-10s",acStack_8a);
        }
        getRate(uVar7,&local_94);
        getRate(uVar9,&local_90);
        goto LAB_0014c1e4;
      }
      goto LAB_0014c288;
    }
  }
  else {
    printk("%-20s",acStack_8a);
    if (*(char *)(iVar1 + 0x150) == '\x01') goto LAB_0014c27c;
LAB_0014c288:
    if (0 < DebugLevel) {
      uVar2 = get_phymode_str(*(byte *)(param_1 + 0xbd) >> 5);
      printk("%-12s",uVar2);
      if (0 < DebugLevel) {
        uVar2 = get_bw_str(((uint)*(ushort *)(param_1 + 0xbc) << 0x17) >> 0x1e);
        printk(&_LC94,uVar2);
      }
    }
  }
  uVar7 = (uint)*(byte *)(param_1 + 0xbc);
  if (*(byte *)(param_1 + 0xbd) < 0x80) {
    snprintf(acStack_8a,0x1e,"%d",uVar7 & 0x3f,iVar15,iVar6,iVar13);
  }
  else {
    snprintf(acStack_8a,0x1e,"%dS-M%d",((int)(uVar7 & 0x3f) >> 4) + 1,uVar7 & 0xf,iVar6,iVar13);
  }
  if (((0 < DebugLevel) && (printk("%-12s",acStack_8a), 0 < DebugLevel)) &&
     (printk(&_LC100,((uint)*(byte *)(param_1 + 0xbd) << 0x1e) >> 0x1f), 0 < DebugLevel)) {
    printk("%-10d",((uint)*(byte *)(param_1 + 0xbd) << 0x1d) >> 0x1f);
  }
LAB_0014c1e4:
  snprintf(acStack_8a,0x1e,"%d/%d",local_94,local_90);
  if ((0 < DebugLevel) && (printk("%-10s",acStack_8a), 0 < DebugLevel)) {
    printk(&_LC73);
  }
  return 0;
}

