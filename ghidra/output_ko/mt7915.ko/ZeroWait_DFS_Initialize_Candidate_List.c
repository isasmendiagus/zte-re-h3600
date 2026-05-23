// module: mt7915.ko
// function: ZeroWait_DFS_Initialize_Candidate_List @ 0x236e98
// size: 856 bytes
//

void ZeroWait_DFS_Initialize_Candidate_List
               (int param_1,uint param_2,char *param_3,uint param_4,char *param_5,byte param_6,
               char *param_7)

{
  char *pcVar1;
  byte bVar2;
  byte *pbVar3;
  byte *pbVar4;
  char cVar5;
  byte *pbVar6;
  undefined1 *puVar7;
  char *pcVar8;
  undefined1 *puVar9;
  byte bVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  char *pcVar14;
  undefined1 *local_98;
  int local_80;
  byte local_63 [63];
  
  uVar11 = 0;
  uVar12 = 0;
  local_80 = 0;
  memset(local_63,0,0x3b);
  local_98 = (undefined1 *)(param_1 + 0x795136);
  bVar10 = 0;
  do {
    if (*(char *)(param_1 + local_80 * 0x20 + 0xa37728) == '\x01') {
      if (DebugLevel < 1) {
        return;
      }
      printk("Channel list init fail during channel switch\n");
      return;
    }
    if (0 < DebugLevel) {
      printk("band_idx: %d\n",local_80);
    }
    pcVar1 = (char *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),local_80);
    if (pcVar1[0x49c] != '\0') {
      pbVar6 = local_63;
      iVar13 = (byte)(pcVar1[0x49c] - 1) + 1;
      pbVar3 = pbVar6;
      pcVar14 = pcVar1;
      do {
        while (cVar5 = *pcVar14, *param_3 != cVar5) {
          if (*param_5 == cVar5) goto LAB_00237028;
LAB_00236fd0:
          if (*param_7 == cVar5) goto LAB_00237054;
LAB_00236fdc:
          pbVar3 = pbVar3 + 1;
          pcVar14 = pcVar14 + 0x14;
          if (pbVar3 == pbVar6 + iVar13) goto LAB_00237084;
        }
        if (uVar11 < param_2) {
          param_3 = param_3 + 2;
        }
        *pbVar3 = *pbVar3 | 4;
        uVar11 = uVar11 + 1 & 0xff;
        if (*param_5 != cVar5) goto LAB_00236fd0;
LAB_00237028:
        if (uVar12 < param_4) {
          param_5 = param_5 + 2;
        }
        *pbVar3 = *pbVar3 | 2;
        uVar12 = uVar12 + 1 & 0xff;
        if (*param_7 != cVar5) goto LAB_00236fdc;
LAB_00237054:
        pbVar4 = pbVar3 + 1;
        pcVar14 = pcVar14 + 0x14;
        bVar2 = bVar10 + 1;
        if (bVar10 < param_6) {
          param_7 = param_7 + 2;
        }
        *pbVar3 = *pbVar3 | 1;
        pbVar3 = pbVar4;
        bVar10 = bVar2;
      } while (pbVar4 != pbVar6 + iVar13);
LAB_00237084:
      pcVar14 = pcVar1;
      do {
        while (bVar2 = pcVar14[8], 6 < bVar2) {
          bVar2 = *pbVar6;
          if (bVar2 != 7) {
            if (bVar2 != 3) goto LAB_002370c8;
            pcVar14[9] = '\x02';
            pcVar14[7] = '\x01';
            pcVar14[10] = '\b';
            pcVar14[0xb] = '\a';
          }
LAB_002370ec:
          pcVar14 = pcVar14 + 0x14;
          pbVar6 = pbVar6 + 1;
          if (pcVar14 == pcVar1 + iVar13 * 0x14) goto LAB_0023713c;
        }
        if (bVar2 == 3) {
          bVar2 = *pbVar6;
          if (bVar2 != 3) {
LAB_002370c8:
            if (bVar2 == 1) {
              pcVar14[9] = '\x01';
              pcVar14[7] = '\x01';
              pcVar14[10] = '\b';
              pcVar14[0xb] = '\a';
            }
            else if (bVar2 == 0) {
              pcVar14[9] = '\0';
              pcVar14[7] = '\x01';
              pcVar14[10] = '\b';
              pcVar14[0xb] = '\a';
            }
          }
          goto LAB_002370ec;
        }
        if (bVar2 != 1) goto LAB_002370ec;
        bVar2 = *pbVar6;
        pcVar8 = pcVar14 + 0x14;
        pbVar6 = pbVar6 + 1;
        if (bVar2 == 0) {
          pcVar14[7] = '\x01';
          pcVar14[9] = '\0';
          pcVar14[10] = '\b';
          pcVar14[0xb] = '\a';
        }
        pcVar14 = pcVar8;
      } while (pcVar8 != pcVar1 + iVar13 * 0x14);
    }
LAB_0023713c:
    cVar5 = '\x04';
    puVar9 = local_98;
    do {
      puVar7 = puVar9 + 0x1e;
      do {
        puVar9 = puVar9 + 1;
        *puVar9 = 0xff;
      } while (puVar9 != puVar7);
      cVar5 = cVar5 + -1;
    } while (cVar5 != '\0');
    uVar11 = 4;
    uVar12 = 0x1e;
    local_98 = local_98 + 0xda;
    DfsBwChQueryAllList(param_1,2,param_1 + 0x795130,1,local_80);
    if (local_80 == 1) {
      return;
    }
    local_80 = 1;
  } while( true );
}

