// module: mt7915.ko
// function: DfsBuildChannelGroupByBw @ 0x232020
// size: 1016 bytes
//

void DfsBuildChannelGroupByBw(int param_1,undefined4 param_2)

{
  undefined1 uVar1;
  byte bVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  byte bVar6;
  uint uVar7;
  byte *pbVar8;
  byte *pbVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  uint uVar13;
  uint uVar14;
  int local_4c;
  uint local_48;
  uint local_44;
  uint local_40;
  uint local_38;
  uint local_34;
  
  iVar3 = HcGetBandByWdev(param_2);
  pbVar4 = (byte *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),iVar3);
  uVar14 = (uint)pbVar4[0x49c];
  if (uVar14 != 0) {
    iVar10 = 0xff;
    uVar11 = 0;
    iVar12 = 0xff;
    uVar13 = 0;
    local_4c = 0xff;
    local_40 = 0xff;
    local_44 = 0xff;
    local_48 = 0xff;
    local_34 = 0;
    local_38 = 0;
    do {
      bVar2 = pbVar4[uVar13 * 0x14];
      if (0xe < bVar2) {
        if (uVar14 == 0) {
          return;
        }
        bVar6 = 0;
        pbVar9 = pbVar4;
        do {
          pbVar8 = pbVar9 + 0x14;
          if (*pbVar9 == bVar2) {
            bVar6 = pbVar9[8] & 2;
          }
          pbVar9 = pbVar8;
        } while (pbVar8 != pbVar4 + ((uVar14 - 1 & 0xff) + 1) * 0x14);
        uVar1 = (undefined1)uVar13;
        if (bVar6 != 0) {
          iVar5 = DfsPrimToCent(bVar2,1);
          if (iVar5 == local_4c) {
            if ((local_48 < 0xf) && (local_38 = local_38 + 1 & 0xff, local_38 < 2)) {
              *(undefined1 *)(param_1 + iVar3 * 0xda + local_48 * 2 + local_38 + 0x7951af) = uVar1;
            }
          }
          else {
            uVar14 = local_48 + 1;
            local_48 = uVar14 & 0xff;
            if ((char)uVar14 < '\x0f') {
              local_38 = 0;
              *(undefined1 *)(param_1 + (iVar3 * 0x6d + local_48) * 2 + 0x7951af) = uVar1;
            }
            else {
              local_38 = 0;
            }
          }
          local_4c = DfsPrimToCent(pbVar4[uVar13 * 0x14],1);
          uVar14 = (uint)pbVar4[0x49c];
          bVar2 = pbVar4[uVar13 * 0x14];
        }
        if (uVar14 == 0) {
          return;
        }
        bVar6 = 0;
        pbVar9 = pbVar4;
        do {
          pbVar8 = pbVar9 + 0x14;
          if (*pbVar9 == bVar2) {
            bVar6 = pbVar9[8] & 4;
          }
          pbVar9 = pbVar8;
        } while (pbVar8 != pbVar4 + ((uVar14 - 1 & 0xff) + 1) * 0x14);
        if (bVar6 != 0) {
          iVar5 = DfsPrimToCent(bVar2,2);
          if (iVar5 == iVar12) {
            if ((local_44 < 9) && (local_34 = local_34 + 1 & 0xff, local_34 < 4)) {
              *(undefined1 *)(param_1 + iVar3 * 0xda + local_44 * 4 + local_34 + 0x7951cd) = uVar1;
            }
          }
          else {
            uVar14 = local_44 + 1;
            local_44 = uVar14 & 0xff;
            if ((char)uVar14 < '\t') {
              local_34 = 0;
              *(undefined1 *)(param_1 + iVar3 * 0xda + (local_44 + 0x24) * 4 + 0x79513d) = uVar1;
            }
            else {
              local_34 = 0;
            }
          }
          iVar12 = DfsPrimToCent(pbVar4[uVar13 * 0x14],2);
          uVar14 = (uint)pbVar4[0x49c];
          bVar2 = pbVar4[uVar13 * 0x14];
          if (uVar14 == 0) {
            return;
          }
        }
        uVar7 = 0;
        bVar6 = 0;
        pbVar9 = pbVar4;
        do {
          uVar7 = uVar7 + 1;
          if (*pbVar9 == bVar2) {
            bVar6 = pbVar9[8] & 8;
          }
          pbVar9 = pbVar9 + 0x14;
        } while ((uVar7 & 0xff) < uVar14);
        if (bVar6 != 0) {
          iVar5 = DfsPrimToCent(bVar2,3);
          if (iVar5 == iVar10) {
            if ((local_40 < 4) && (uVar11 = uVar11 + 1 & 0xff, uVar11 < 8)) {
              *(undefined1 *)(param_1 + iVar3 * 0xda + local_40 * 8 + uVar11 + 0x7951f1) = uVar1;
            }
          }
          else {
            uVar14 = local_40 + 1;
            local_40 = uVar14 & 0xff;
            if ((char)uVar14 < '\x04') {
              uVar11 = 0;
              *(undefined1 *)(param_1 + iVar3 * 0xda + (local_40 + 0x17) * 8 + 0x795139) = uVar1;
            }
            else {
              uVar11 = 0;
            }
          }
          iVar10 = DfsPrimToCent(pbVar4[uVar13 * 0x14],3);
          uVar14 = (uint)pbVar4[0x49c];
        }
      }
      uVar13 = uVar13 + 1 & 0xff;
    } while (uVar13 < uVar14);
  }
  return;
}

