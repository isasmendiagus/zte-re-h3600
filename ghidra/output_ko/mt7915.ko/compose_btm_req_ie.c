// module: mt7915.ko
// function: compose_btm_req_ie @ 0x228f28
// size: 1268 bytes
//

undefined4
compose_btm_req_ie(undefined4 param_1,undefined4 param_2,byte *param_3,undefined4 *param_4,
                  int param_5)

{
  byte bVar1;
  bool bVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  byte bVar7;
  uint uVar8;
  byte bVar9;
  int iVar10;
  undefined4 uVar11;
  int iVar12;
  uint uVar13;
  byte bVar14;
  char cVar15;
  char cVar16;
  undefined4 *puVar17;
  undefined4 *local_40;
  uint local_39;
  undefined4 local_35;
  undefined2 local_31;
  uint local_2f;
  char local_2b;
  undefined1 local_2a;
  char local_29;
  
  puVar17 = &DebugLevel;
  iVar12 = param_5 + 0x43;
  if (DebugLevel < 3) {
    puVar17 = (undefined4 *)0x4;
  }
  local_40 = (undefined4 *)0x0;
  if (DebugLevel < 3) {
    iVar6 = 3;
    iVar4 = 1;
    local_40 = (undefined4 *)0x0;
  }
  else {
    printk(&_LC4,"compose_btm_req_ie");
    iVar4 = (int)local_40 + 1;
    iVar6 = (int)local_40 + 3;
    puVar17 = local_40 + 1;
  }
  if (*(short *)(param_5 + 8) == 0) {
    bVar9 = *(byte *)(param_5 + 7) & 0xfb;
  }
  else {
    bVar9 = *(byte *)(param_5 + 7) | 4;
  }
  *(byte *)(param_5 + 7) = bVar9;
  if (*(short *)(param_5 + 0x17) == 0) {
    bVar9 = bVar9 & 0xf7;
  }
  else {
    bVar9 = bVar9 | 8;
  }
  *(byte *)(param_5 + 7) = bVar9;
  if (*(char *)(param_5 + 0x19) == '\0') {
    bVar9 = bVar9 & 0xef;
  }
  else {
    bVar9 = bVar9 | 0x10;
  }
  *(byte *)(param_5 + 7) = bVar9 & 0xfe;
  param_3[(int)local_40] = bVar9 & 0xfe;
  *(undefined2 *)(param_3 + iVar4) = *(undefined2 *)(param_5 + 8);
  param_3[iVar6] = *(byte *)(param_5 + 10);
  bVar9 = *(byte *)(param_5 + 7);
  local_40 = puVar17;
  if ((bVar9 & 8) != 0) {
    WNM_InsertBSSTerminationSubIE
              (param_1,param_3 + (int)puVar17,&local_40,*(undefined2 *)(param_5 + 0x17),
               *(undefined4 *)(param_5 + 0xf),*(undefined4 *)(param_5 + 0x13),
               *(undefined2 *)(param_5 + 0x17));
    bVar9 = *(byte *)(param_5 + 7);
  }
  if ((bVar9 & 0x10) != 0) {
    iVar4 = (int)local_40 + 1;
    param_3[(int)local_40] = *(byte *)(param_5 + 0x19);
    memcpy(param_3 + iVar4,(void *)(param_5 + 0x1a),(uint)*(byte *)(param_5 + 0x19));
    local_40 = (undefined4 *)(iVar4 + (uint)*(byte *)(param_5 + 0x19));
  }
  *param_4 = local_40;
  if (*(char *)(param_5 + 0x42) != '\0') {
    uVar13 = 0;
    iVar4 = param_5 + 0x48;
    bVar2 = false;
    do {
      cVar15 = *(char *)(iVar12 + 1);
      if ((((cVar15 == '\0') || (cVar16 = *(char *)(iVar12 + 2), cVar16 == '\0')) ||
          (uVar8 = (uint)*(ushort *)(iVar12 + 3), uVar8 == 0)) ||
         (((bVar9 = *(byte *)(iVar12 + 0xc), bVar9 == 0 ||
           (bVar14 = *(byte *)(iVar12 + 0xd), bVar14 == 0)) ||
          ((bVar7 = *(byte *)(iVar12 + 0x11), bVar7 == 0 || (bVar2)))))) {
        iVar6 = get_scan_tab_by_wdev(param_1,param_2);
        iVar5 = BssTableSearch(iVar6,iVar4,*(undefined1 *)(iVar4 + -5));
        if (iVar5 != -1) {
          if (*(char *)(iVar12 + 2) == '\0') {
            *(undefined1 *)(iVar12 + 2) = *(undefined1 *)(iVar5 * 0xaf4 + iVar6 + 0x6c7);
          }
          if (*(short *)(iVar12 + 3) == 0) {
            *(undefined2 *)(iVar12 + 3) = *(undefined2 *)(iVar5 * 0xaf4 + iVar6 + 0x92);
          }
          if (*(char *)(iVar12 + 0xc) == '\0') {
            *(byte *)(iVar12 + 0xc) = (byte)*(undefined4 *)(iVar5 * 0xaf4 + iVar6 + 0xad0) & 1;
          }
          if (*(char *)(iVar12 + 0xd) == '\0') {
            *(byte *)(iVar12 + 0xd) =
                 (byte)((uint)(*(int *)(iVar5 * 0xaf4 + iVar6 + 0xad0) << 0x1d) >> 0x1f);
          }
          if (*(char *)(iVar12 + 0x11) == '\0') {
            *(bool *)(iVar12 + 0x11) = *(char *)(iVar5 * 0xaf4 + iVar6 + 0x6c3) != '\0';
          }
          iVar10 = iVar5 * 0xaf4 + iVar6;
          uVar8 = *(uint *)(iVar10 + 0xad0);
          if (*(byte *)(iVar10 + 0x14) < 0xf) {
            if ((uVar8 & 1) == 0) {
              if ((*(byte *)(iVar10 + 0x3c) & 1) == 0) {
                if (4 < *(byte *)(iVar10 + 0x2e)) goto LAB_00229354;
              }
              else {
                *(undefined1 *)(iVar10 + 0x6c8) = 6;
              }
              goto LAB_0022911c;
            }
LAB_00229280:
            *(undefined1 *)(iVar10 + 0x6c8) = 7;
            cVar15 = *(char *)(iVar12 + 1);
          }
          else {
            if ((uVar8 & 1) == 0) {
LAB_00229354:
              *(undefined1 *)(iVar10 + 0x6c8) = 4;
            }
            else {
              if ((uVar8 & 4) == 0) goto LAB_00229280;
              *(undefined1 *)(iVar10 + 0x6c8) = 9;
            }
LAB_0022911c:
            cVar15 = *(char *)(iVar12 + 1);
          }
          if (cVar15 == '\0') {
            uVar8 = (uint)*(ushort *)(iVar12 + 3);
            bVar7 = *(byte *)(iVar12 + 0x11);
            bVar9 = *(byte *)(iVar12 + 0xc);
            bVar2 = true;
            bVar14 = *(byte *)(iVar12 + 0xd);
            cVar16 = *(char *)(iVar12 + 2);
            cVar15 = *(char *)(iVar5 * 0xaf4 + iVar6 + 0x6c8);
            *(char *)(iVar12 + 1) = cVar15;
          }
          else {
            bVar7 = *(byte *)(iVar12 + 0x11);
            bVar9 = *(byte *)(iVar12 + 0xc);
            bVar14 = *(byte *)(iVar12 + 0xd);
            cVar16 = *(char *)(iVar12 + 2);
            uVar8 = (uint)*(ushort *)(iVar12 + 3);
            bVar2 = true;
          }
          goto LAB_00229144;
        }
        if (DebugLevel < 2) {
          bVar2 = true;
        }
        else {
          bVar2 = true;
          printk("%s() bss not found \n","compose_btm_req_ie");
        }
      }
      else {
LAB_00229144:
        bVar1 = *(byte *)(iVar12 + 0xe);
        bVar3 = 0;
        if (bVar1 != 0) {
          bVar3 = bVar1 & 3;
        }
        if (bVar1 == 0) {
          bVar3 = 3;
        }
        local_35 = *(undefined4 *)(iVar12 + 5);
        local_39 = (uint)CONCAT11((byte)((uVar8 << 0x11) >> 0x1f) | (byte)((uVar8 >> 0xf) << 1) |
                                  (bVar7 & 1) << 2 | (bVar9 & 1) << 3 | (bVar14 & 1) << 4,
                                  bVar3 | (*(byte *)(iVar12 + 0xf) & 1) << 2 |
                                  (*(byte *)(iVar12 + 0x10) & 1) << 3 |
                                  (byte)(((uVar8 << 0x17) >> 0x1f) << 4) |
                                  (byte)(((uVar8 << 0x16) >> 0x1f) << 5) |
                                  (byte)(((uVar8 << 0x14) >> 0x1f) << 6) |
                                  (byte)(((uVar8 << 0x13) >> 0x1f) << 7));
        local_31 = *(undefined2 *)(iVar12 + 9);
        local_2a = *(undefined1 *)(iVar4 + -5);
        local_2f = local_39;
        if (*(char *)(iVar12 + 0xb) == '\0') {
          uVar11 = 0xd;
        }
        else {
          uVar11 = 0x10;
        }
        local_2b = cVar16;
        local_29 = cVar15;
        RRM_InsertNeighborRepIE(param_1,param_3 + (int)local_40,&local_40,uVar11,&local_35);
        if (*(char *)(iVar12 + 0xb) != '\0') {
          RRM_InsertPreferenceSubIE(param_1,param_3 + (int)local_40,&local_40);
        }
      }
      uVar13 = uVar13 + 1;
      iVar12 = iVar12 + 0x12;
      iVar4 = iVar4 + 0x12;
    } while (uVar13 < *(byte *)(param_5 + 0x42));
    if ((undefined4 *)*param_4 < local_40) {
      *param_4 = local_40;
      *param_3 = *param_3 | 1;
    }
  }
  return 0;
}

