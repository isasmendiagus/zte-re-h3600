// module: mt7915.ko
// function: DfsBwChQueryByDefault @ 0x23300c
// size: 1444 bytes
//

uint DfsBwChQueryByDefault
               (int param_1,uint param_2,int param_3,int param_4,undefined4 param_5,char param_6,
               byte param_7)

{
  byte *pbVar1;
  uint uVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  byte bVar7;
  uint extraout_r1;
  uint extraout_r1_00;
  uint extraout_r1_01;
  byte *pbVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  bool bVar13;
  undefined8 uVar14;
  uint local_48;
  int local_44;
  
  uVar2 = (uint)param_7;
  local_44 = param_4;
LAB_00233058:
  do {
    pbVar3 = (byte *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar2);
    if (*(char *)(param_3 + 0x2b0) == '\0') {
      uVar6 = RandomByte(param_1);
      __aeabi_uidivmod(uVar6,pbVar3[0x49c]);
      return (uint)pbVar3[(extraout_r1 & 0xff) * 0x14] | param_2 << 8;
    }
    uVar12 = (uint)pbVar3[0x49c];
    if (uVar12 != 0) {
      uVar9 = 0;
      local_48 = 0;
      do {
        bVar7 = pbVar3[uVar9 * 0x14];
        if ((&DAT_0036b862)[param_1] == '\0') {
LAB_0023311c:
          if (param_6 == '\x01') {
            iVar4 = RadarChannelCheck(param_1);
            if (iVar4 != 0) {
              bVar7 = pbVar3[uVar9 * 0x14];
              uVar12 = (uint)pbVar3[0x49c];
              goto LAB_00233128;
            }
            goto LAB_002331f4;
          }
LAB_00233128:
          if (0xe < bVar7) {
            if (uVar12 == 0) break;
            uVar10 = 0;
            pbVar8 = pbVar3;
            do {
              while (*pbVar8 == bVar7) {
                pbVar1 = pbVar8 + 8;
                pbVar8 = pbVar8 + 0x14;
                if (param_2 == 6) {
                  uVar10 = *pbVar1 & 4;
                }
                else {
                  uVar10 = (uint)*pbVar1 & 1 << (param_2 & 0xff) & 0xffU;
                }
                if (pbVar8 == pbVar3 + ((uVar12 - 1 & 0xff) + 1) * 0x14) goto LAB_00233194;
              }
              pbVar8 = pbVar8 + 0x14;
            } while (pbVar8 != pbVar3 + ((uVar12 - 1 & 0xff) + 1) * 0x14);
LAB_00233194:
            if ((uVar10 != 0) &&
               (((*(short *)(pbVar3 + uVar9 * 0x14 + 0xc) != 0 || (pbVar3[uVar9 * 0x14 + 7] == 0))
                || (pbVar3[uVar9 * 0x14 + 9] != param_2)))) {
              iVar4 = DfsCheckBwGroupAllAvailable(uVar9,param_2,param_1,uVar2);
              if (iVar4 != 0) {
                iVar4 = DfsPrimToCent(pbVar3[uVar9 * 0x14],*(undefined1 *)(param_3 + uVar2 + 4));
                iVar5 = DfsPrimToCent(*(undefined1 *)(param_3 + uVar2),
                                      *(undefined1 *)(param_3 + uVar2 + 4));
                if (iVar4 != iVar5) {
                  iVar4 = DfsPrimToCent(pbVar3[uVar9 * 0x14],param_2);
                  iVar5 = DfsPrimToCent(*(undefined1 *)(param_3 + uVar2),param_2);
                  if (iVar4 != iVar5) {
                    if (local_44 == 1) {
                      if ((*(short *)(pbVar3 + uVar9 * 0x14 + 0xc) == 0) &&
                         (pbVar3[uVar9 * 0x14 + 7] == 0)) goto LAB_002332fc;
                    }
                    else if ((local_44 == 2) && (*(short *)(pbVar3 + uVar9 * 0x14 + 0xc) == 0)) {
LAB_002332fc:
                      *(char *)(param_3 + param_2 * 0x1e + uVar2 * 0xda + local_48 + 7) =
                           (char)uVar9;
                      local_48 = local_48 + 1 & 0xff;
                    }
                  }
                }
              }
LAB_002331f4:
              uVar12 = (uint)pbVar3[0x49c];
            }
          }
        }
        else if ((&DAT_0036b863)[param_1] != bVar7) {
          pbVar8 = &DAT_0036b863 + param_1;
          do {
            if (pbVar8 == &DAT_0036b863 + param_1 + (uint)(byte)((&DAT_0036b862)[param_1] - 1))
            goto LAB_0023311c;
            pbVar8 = pbVar8 + 1;
          } while (*pbVar8 != bVar7);
        }
        uVar9 = uVar9 + 1 & 0xff;
      } while (uVar9 < uVar12);
      if (local_48 != 0) {
        bVar7 = *(byte *)(param_3 + uVar2 * 0xda + param_2 * 0x1e + 7);
        if (*(char *)(param_1 + 0x795075) != '\0') goto LAB_002334b0;
        iVar4 = (short)(ushort)param_7 * 0xda + 7;
        pbVar8 = (byte *)(param_3 + iVar4 + param_2 * 0x1e);
        break;
      }
    }
    if (local_44 != 1) goto LAB_0023335c;
    local_44 = 2;
  } while( true );
LAB_00233490:
  iVar5 = DfsCacRestrictBand(param_1,param_2,pbVar3[(uint)bVar7 * 0x14],0);
  if (iVar5 == 0) {
LAB_002334b0:
    uVar12 = 1;
LAB_002334b4:
    uVar6 = RandomByte(param_1);
    __aeabi_uidivmod(uVar6,local_48);
    bVar13 = *(char *)(param_1 + 0x795075) != '\0';
    uVar9 = uVar2;
    if (bVar13) {
      uVar9 = 0;
    }
    uVar10 = param_3 + uVar2 * 0xda + param_2 * 0x1e + (extraout_r1_00 & 0xff);
    uVar11 = (uint)*(byte *)(uVar10 + 7);
    if (!bVar13) {
      uVar14 = DfsCacRestrictBand(param_1,param_2,pbVar3[uVar11 * 0x14]);
      uVar10 = (uint)((ulonglong)uVar14 >> 0x20);
      uVar9 = 0;
      if ((int)uVar14 != 0) {
        uVar9 = 1;
      }
    }
    while ((uVar9 & uVar12) != 0) {
      while( true ) {
        uVar6 = RandomByte(param_1,uVar10);
        __aeabi_uidivmod(uVar6,local_48);
        uVar9 = 0;
        uVar11 = (uint)*(byte *)(param_3 + uVar2 * 0xda + param_2 * 0x1e + (extraout_r1_01 & 0xff) +
                                7);
        uVar10 = param_2;
        if (*(char *)(param_1 + 0x795075) != '\0') break;
        uVar14 = DfsCacRestrictBand(param_1,param_2,pbVar3[uVar11 * 0x14]);
        uVar10 = (uint)((ulonglong)uVar14 >> 0x20);
        if (((int)uVar14 != 0 & uVar12) == 0) goto LAB_00233594;
      }
    }
LAB_00233594:
    return (uint)pbVar3[uVar11 * 0x14] | param_2 << 8;
  }
  if (pbVar8 == (byte *)(param_3 + iVar4 + (local_48 - 1 & 0xff) + param_2 * 0x1e)) {
    uVar12 = 0;
    goto LAB_002334b4;
  }
  pbVar8 = pbVar8 + 1;
  bVar7 = *pbVar8;
  goto LAB_00233490;
LAB_0023335c:
  if (param_2 == 0 || local_44 != 2) {
    return 0;
  }
  if (uVar12 != 0) {
    pbVar8 = pbVar3 + ((uVar12 - 1 & 0xff) + 1) * 0x14;
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
  local_44 = 1;
  param_2 = param_2 - 1 & 0xff;
  goto LAB_00233058;
}

