// module: mt7915.ko
// function: DfsBwChQueryAllList @ 0x2335b0
// size: 840 bytes
//

void DfsBwChQueryAllList(int param_1,uint param_2,int param_3,int param_4,byte param_5)

{
  byte *pbVar1;
  byte bVar2;
  byte *pbVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  byte *pbVar8;
  uint uVar9;
  uint uVar10;
  uint local_44;
  
  uVar7 = (uint)param_5;
  if (*(char *)(param_3 + 0x2b0) != '\0') {
    do {
      pbVar3 = (byte *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar7);
      uVar4 = (uint)pbVar3[0x49c];
      if (uVar4 == 0) {
        if (param_2 == 0) {
          return;
        }
      }
      else {
        uVar9 = 0;
        local_44 = 0;
        do {
          while( true ) {
            bVar2 = pbVar3[uVar9 * 0x14];
            if ((&DAT_0036b862)[param_1] == '\0') break;
            if ((&DAT_0036b863)[param_1] != bVar2) {
              pbVar8 = &DAT_0036b863 + param_1;
              do {
                if (pbVar8 == &DAT_0036b863 + param_1 + (uint)(byte)((&DAT_0036b862)[param_1] - 1))
                goto LAB_002336a8;
                pbVar8 = pbVar8 + 1;
              } while (*pbVar8 != bVar2);
            }
LAB_002337bc:
            uVar9 = uVar9 + 1 & 0xff;
            if (uVar4 <= uVar9) goto LAB_002337cc;
          }
LAB_002336a8:
          if (bVar2 < 0xf) goto LAB_002337bc;
          uVar10 = 0;
          pbVar8 = pbVar3;
          do {
            while (*pbVar8 != bVar2) {
              pbVar8 = pbVar8 + 0x14;
              if (pbVar8 == pbVar3 + ((uVar4 - 1 & 0xff) + 1) * 0x14) goto LAB_00233708;
            }
            pbVar1 = pbVar8 + 8;
            pbVar8 = pbVar8 + 0x14;
            if (param_2 == 6) {
              uVar10 = *pbVar1 & 4;
            }
            else {
              uVar10 = (uint)*pbVar1 & 1 << (param_2 & 0xff) & 0xffU;
            }
          } while (pbVar8 != pbVar3 + ((uVar4 - 1 & 0xff) + 1) * 0x14);
LAB_00233708:
          if ((uVar10 == 0) ||
             (((*(short *)(pbVar3 + uVar9 * 0x14 + 0xc) == 0 && (pbVar3[uVar9 * 0x14 + 7] != 0)) &&
              (pbVar3[uVar9 * 0x14 + 9] <= param_2)))) goto LAB_002337bc;
          iVar5 = DfsCheckBwGroupAllAvailable(uVar9,param_2,param_1,uVar7);
          if (iVar5 == 0) {
LAB_00233868:
            bVar2 = pbVar3[0x49c];
          }
          else {
            if (param_4 != 1) {
LAB_0023376c:
              if (*(short *)(pbVar3 + uVar9 * 0x14 + 0xc) == 0) {
                *(char *)(param_3 + param_2 * 0x1e + uVar7 * 0xda + local_44 + 7) = (char)uVar9;
                uVar4 = (uint)pbVar3[0x49c];
                local_44 = local_44 + 1 & 0xff;
                goto LAB_002337bc;
              }
              if (2 < DebugLevel) {
                printk("%s(): NOP ! =0 (%d)\n","DfsBwChQueryAllList");
              }
              goto LAB_00233868;
            }
            iVar5 = DfsPrimToCent(pbVar3[uVar9 * 0x14],*(undefined1 *)(param_3 + uVar7 + 4));
            iVar6 = DfsPrimToCent(*(undefined1 *)(param_3 + uVar7),
                                  *(undefined1 *)(param_3 + uVar7 + 4));
            if (iVar5 == iVar6) goto LAB_00233868;
            iVar5 = DfsPrimToCent(pbVar3[uVar9 * 0x14],param_2);
            iVar6 = DfsPrimToCent(*(undefined1 *)(param_3 + uVar7),param_2);
            if (iVar5 != iVar6) goto LAB_0023376c;
            bVar2 = pbVar3[0x49c];
          }
          uVar4 = (uint)bVar2;
          uVar9 = uVar9 + 1 & 0xff;
        } while (uVar9 < uVar4);
LAB_002337cc:
        if (param_2 == 0) {
          return;
        }
        if (uVar4 != 0) {
          pbVar8 = pbVar3 + ((uVar4 - 1 & 0xff) + 1) * 0x14;
          do {
            if ((*(short *)(pbVar3 + 0xc) != 0) && (pbVar3[9] == param_2)) {
              *(short *)(pbVar3 + 10) = *(short *)(pbVar3 + 0xc);
              pbVar3[0xc] = 0;
              pbVar3[0xd] = 0;
              pbVar3[7] = pbVar3[7] + 1;
            }
            pbVar3 = pbVar3 + 0x14;
          } while (pbVar3 != pbVar8);
        }
      }
      param_2 = param_2 - 1 & 0xff;
    } while (*(char *)(param_3 + 0x2b0) != '\0');
  }
  return;
}

