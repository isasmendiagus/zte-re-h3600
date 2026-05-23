// module: mt7915.ko
// function: compose_rrm_nrrsp_ie @ 0x220ecc
// size: 840 bytes
//

void compose_rrm_nrrsp_ie
               (undefined4 param_1,undefined4 param_2,int param_3,int *param_4,int param_5,
               byte param_6)

{
  bool bVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  byte bVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  byte bVar10;
  char cVar11;
  char cVar12;
  byte bVar13;
  uint local_39;
  undefined4 local_35;
  undefined2 local_31;
  uint local_2f;
  char local_2b;
  undefined1 local_2a;
  char local_29;
  
  if (param_6 != 0) {
    iVar8 = param_5 + 5;
    uVar9 = 0;
    bVar1 = false;
    do {
      cVar11 = *(char *)(param_5 + 1);
      if ((((cVar11 == '\0') || (cVar12 = *(char *)(param_5 + 2), cVar12 == '\0')) ||
          (uVar6 = (uint)*(ushort *)(param_5 + 3), uVar6 == 0)) ||
         (((bVar5 = *(byte *)(param_5 + 0xc), bVar5 == 0 ||
           (bVar10 = *(byte *)(param_5 + 0xd), bVar10 == 0)) ||
          ((bVar13 = *(byte *)(param_5 + 0x11), bVar13 == 0 || (bVar1)))))) {
        iVar3 = get_scan_tab_by_wdev(param_1,param_2);
        iVar4 = BssTableSearch(iVar3,iVar8,*(undefined1 *)(iVar8 + -5));
        if (iVar4 != -1) {
          if (*(char *)(param_5 + 2) == '\0') {
            *(undefined1 *)(param_5 + 2) = *(undefined1 *)(iVar4 * 0xaf4 + iVar3 + 0x6c7);
          }
          if (*(short *)(param_5 + 3) == 0) {
            *(undefined2 *)(param_5 + 3) = *(undefined2 *)(iVar4 * 0xaf4 + iVar3 + 0x92);
          }
          if (*(char *)(param_5 + 0xc) == '\0') {
            *(byte *)(param_5 + 0xc) = (byte)*(undefined4 *)(iVar4 * 0xaf4 + iVar3 + 0xad0) & 1;
          }
          if (*(char *)(param_5 + 0xd) == '\0') {
            *(byte *)(param_5 + 0xd) =
                 (byte)((uint)(*(int *)(iVar4 * 0xaf4 + iVar3 + 0xad0) << 0x1d) >> 0x1f);
          }
          if (*(char *)(param_5 + 0x11) == '\0') {
            *(bool *)(param_5 + 0x11) = *(char *)(iVar4 * 0xaf4 + iVar3 + 0x6c3) != '\0';
          }
          iVar7 = iVar4 * 0xaf4 + iVar3;
          uVar6 = *(uint *)(iVar7 + 0xad0);
          if (*(byte *)(iVar7 + 0x14) < 0xf) {
            if ((uVar6 & 1) == 0) {
              if ((*(byte *)(iVar7 + 0x3c) & 1) == 0) {
                if (4 < *(byte *)(iVar7 + 0x2e)) goto LAB_002211d4;
              }
              else {
                *(undefined1 *)(iVar7 + 0x6c8) = 6;
              }
              goto LAB_00221000;
            }
LAB_0022111c:
            *(undefined1 *)(iVar7 + 0x6c8) = 7;
            cVar11 = *(char *)(param_5 + 1);
          }
          else {
            if ((uVar6 & 1) == 0) {
LAB_002211d4:
              *(undefined1 *)(iVar7 + 0x6c8) = 4;
            }
            else {
              if ((uVar6 & 4) == 0) goto LAB_0022111c;
              *(undefined1 *)(iVar7 + 0x6c8) = 9;
            }
LAB_00221000:
            cVar11 = *(char *)(param_5 + 1);
          }
          if (cVar11 == '\0') {
            uVar6 = (uint)*(ushort *)(param_5 + 3);
            bVar13 = *(byte *)(param_5 + 0x11);
            bVar5 = *(byte *)(param_5 + 0xc);
            bVar1 = true;
            bVar10 = *(byte *)(param_5 + 0xd);
            cVar12 = *(char *)(param_5 + 2);
            cVar11 = *(char *)(iVar4 * 0xaf4 + iVar3 + 0x6c8);
            *(char *)(param_5 + 1) = cVar11;
          }
          else {
            bVar13 = *(byte *)(param_5 + 0x11);
            bVar5 = *(byte *)(param_5 + 0xc);
            bVar10 = *(byte *)(param_5 + 0xd);
            cVar12 = *(char *)(param_5 + 2);
            uVar6 = (uint)*(ushort *)(param_5 + 3);
            bVar1 = true;
          }
          goto LAB_00221028;
        }
        if (DebugLevel < 2) {
          bVar1 = true;
        }
        else {
          bVar1 = true;
          printk("%s() bss not found \n","compose_rrm_nrrsp_ie");
        }
      }
      else {
LAB_00221028:
        if (*(byte *)(param_5 + 0xe) == 0) {
          bVar2 = 3;
        }
        else {
          bVar2 = *(byte *)(param_5 + 0xe) & 3;
        }
        local_35 = *(undefined4 *)(param_5 + 5);
        local_31 = *(undefined2 *)(param_5 + 9);
        local_39 = (uint)CONCAT11((byte)((uVar6 << 0x11) >> 0x1f) | (byte)((uVar6 >> 0xf) << 1) |
                                  (bVar13 & 1) << 2 | (bVar5 & 1) << 3 | (bVar10 & 1) << 4,
                                  bVar2 | (*(byte *)(param_5 + 0xf) & 1) << 2 |
                                  (*(byte *)(param_5 + 0x10) & 1) << 3 |
                                  (byte)(((uVar6 << 0x17) >> 0x1f) << 4) |
                                  (byte)(((uVar6 << 0x16) >> 0x1f) << 5) |
                                  (byte)(((uVar6 << 0x14) >> 0x1f) << 6) |
                                  (byte)(((uVar6 << 0x13) >> 0x1f) << 7));
        local_2a = *(undefined1 *)(iVar8 + -5);
        local_2f = local_39;
        local_2b = cVar12;
        local_29 = cVar11;
        RRM_InsertNeighborRepIE(param_1,param_3 + *param_4,param_4,0xd,&local_35);
      }
      uVar9 = uVar9 + 1;
      param_5 = param_5 + 0x12;
      iVar8 = iVar8 + 0x12;
    } while (uVar9 != param_6);
  }
  return;
}

