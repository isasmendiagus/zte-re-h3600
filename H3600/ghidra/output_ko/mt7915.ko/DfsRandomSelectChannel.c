// module: mt7915.ko
// function: DfsRandomSelectChannel @ 0x2340d8
// size: 1380 bytes
//

uint DfsRandomSelectChannel(int param_1,int param_2,int param_3,int param_4,byte param_5)

{
  byte *pbVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  byte bVar5;
  byte bVar6;
  uint extraout_r1;
  uint extraout_r1_00;
  uint extraout_r1_01;
  uint uVar7;
  uint uVar8;
  int iVar9;
  byte *pbVar10;
  byte *pbVar11;
  uint uVar12;
  ushort uVar13;
  ushort uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint local_74;
  byte abStack_63 [63];
  
  uVar8 = (uint)param_5;
  memset(abStack_63,0,0x3b);
  pbVar1 = (byte *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar8);
  if (*(char *)(param_2 + 0x2b0) == '\0') {
    uVar2 = RandomByte(param_1);
    __aeabi_uidivmod(uVar2,pbVar1[0x49c]);
    local_74 = (uint)pbVar1[(extraout_r1_00 & 0xff) * 0x14];
    if (local_74 == 0) {
      return (uint)*pbVar1;
    }
  }
  else {
    uVar15 = (uint)pbVar1[0x49c];
    if (uVar15 != 0) {
      uVar12 = 0;
      local_74 = 0;
LAB_00234160:
      do {
        if (*(short *)(pbVar1 + uVar12 * 0x14 + 0xc) == 0) {
          bVar5 = pbVar1[uVar12 * 0x14];
          if ((&DAT_0036b862)[param_1] == '\0') {
LAB_002341c8:
            if (0xe < bVar5) {
              if (param_3 == 0) {
LAB_002341dc:
                iVar9 = param_2 + uVar8;
                uVar7 = (uint)*(byte *)(iVar9 + 4);
                if (uVar15 == 0) break;
                uVar17 = 0;
                pbVar10 = pbVar1;
                do {
                  while (*pbVar10 != bVar5) {
                    pbVar10 = pbVar10 + 0x14;
                    if (pbVar10 == pbVar1 + ((uVar15 - 1 & 0xff) + 1) * 0x14) goto LAB_0023425c;
                  }
                  pbVar11 = pbVar10 + 8;
                  pbVar10 = pbVar10 + 0x14;
                  if (uVar7 == 6) {
                    uVar17 = *pbVar11 & 4;
                  }
                  else {
                    uVar17 = (uint)*pbVar11 & 1 << uVar7 & 0xffU;
                  }
                } while (pbVar10 != pbVar1 + ((uVar15 - 1 & 0xff) + 1) * 0x14);
LAB_0023425c:
                if (uVar17 == 0) goto LAB_002342a4;
                if (param_4 != 0) {
                  if (uVar7 == 6) {
                    iVar3 = DfsPrimToCent(bVar5,2);
                    iVar4 = DfsPrimToCent(param_4,2);
                    if (iVar3 == iVar4) goto LAB_002342a0;
                    bVar5 = pbVar1[uVar12 * 0x14];
                    uVar7 = (uint)*(byte *)(iVar9 + 4);
                  }
                  if (*(char *)(param_1 + 0x79504d) == '\x01') {
                    iVar3 = DfsPrimToCent(bVar5,uVar7);
                    iVar4 = DfsPrimToCent(param_4,*(undefined1 *)(iVar9 + 4));
                    if (iVar3 == iVar4) goto LAB_002342a0;
                    bVar5 = pbVar1[uVar12 * 0x14];
                    uVar7 = (uint)*(byte *)(iVar9 + 4);
                  }
                }
                iVar9 = DfsDedicatedCheckChBwValid(param_1,bVar5,uVar7,uVar8);
                if (iVar9 != 0) {
                  uVar15 = (uint)pbVar1[0x49c];
                  iVar9 = uVar12 * 0x14;
                  uVar12 = uVar12 + 1 & 0xff;
                  uVar7 = local_74 + 1 & 0xff;
                  abStack_63[local_74] = pbVar1[iVar9];
                  local_74 = uVar7;
                  if (uVar15 <= uVar12) break;
                  goto LAB_00234160;
                }
              }
              else {
                iVar9 = RadarChannelCheck(param_1);
                if (iVar9 == 0) {
                  bVar5 = pbVar1[uVar12 * 0x14];
                  uVar15 = (uint)pbVar1[0x49c];
                  goto LAB_002341dc;
                }
              }
LAB_002342a0:
              uVar15 = (uint)pbVar1[0x49c];
            }
          }
          else if ((&DAT_0036b863)[param_1] != bVar5) {
            pbVar10 = &DAT_0036b863 + param_1;
            do {
              if (pbVar10 == &DAT_0036b863 + param_1 + (uint)(byte)((&DAT_0036b862)[param_1] - 1))
              goto LAB_002341c8;
              pbVar10 = pbVar10 + 1;
            } while (*pbVar10 != bVar5);
          }
        }
LAB_002342a4:
        uVar12 = uVar12 + 1 & 0xff;
      } while (uVar12 < uVar15);
      if (local_74 != 0) {
        uVar2 = RandomByte(param_1);
        __aeabi_uidivmod(uVar2,local_74);
        return (uint)abStack_63[extraout_r1 & 0xff];
      }
    }
    iVar9 = param_2 + uVar8;
    *(undefined1 *)(iVar9 + 699) = 0;
    if (*(char *)(iVar9 + 4) == '\x06') {
      *(undefined1 *)(iVar9 + 699) = 1;
      do {
        do {
          uVar2 = RandomByte(param_1);
          bVar5 = pbVar1[0x49c];
          __aeabi_uidivmod(uVar2,bVar5);
          local_74 = (uint)pbVar1[(extraout_r1_01 & 0xff) * 0x14];
        } while (bVar5 == 0);
        bVar6 = 0;
        pbVar10 = pbVar1;
        do {
          pbVar11 = pbVar10 + 0x14;
          if (*pbVar10 == local_74) {
            bVar6 = pbVar10[8] & 4;
          }
          pbVar10 = pbVar11;
        } while (pbVar11 != pbVar1 + ((byte)(bVar5 - 1) + 1) * 0x14);
      } while (bVar6 == 0);
    }
    else {
      uVar15 = DfsBwChQueryByDefault(param_1,3,param_2,1,1,0,uVar8);
      local_74 = uVar15 & 0xff;
      *(char *)(iVar9 + 4) = (char)(uVar15 >> 8);
      if (local_74 == 0) {
        *(undefined1 *)(iVar9 + 699) = 1;
        uVar15 = (uint)pbVar1[0x49c];
        if (uVar15 != 0) {
          uVar12 = 0;
          uVar14 = 0xffff;
          do {
            uVar7 = local_74;
            uVar13 = uVar14;
            if ((*(ushort *)(pbVar1 + uVar12 * 0x14 + 0xc) < uVar14) &&
               (uVar17 = (uint)pbVar1[uVar12 * 0x14], 0xe < uVar17)) {
              uVar16 = 0;
              pbVar10 = pbVar1;
              do {
                while (*pbVar10 != uVar17) {
                  pbVar10 = pbVar10 + 0x14;
                  if (pbVar10 == pbVar1 + ((uVar15 - 1 & 0xff) + 1) * 0x14) goto LAB_002343d0;
                }
                pbVar11 = pbVar10 + 8;
                pbVar10 = pbVar10 + 0x14;
                if (*(byte *)(iVar9 + 4) == 6) {
                  uVar16 = *pbVar11 & 4;
                }
                else {
                  uVar16 = 1 << (uint)*(byte *)(iVar9 + 4) & 0xffU & (uint)*pbVar11;
                }
              } while (pbVar10 != pbVar1 + ((uVar15 - 1 & 0xff) + 1) * 0x14);
LAB_002343d0:
              if ((uVar16 != 0) &&
                 (uVar7 = uVar17, uVar13 = *(ushort *)(pbVar1 + uVar12 * 0x14 + 0xc), param_4 != 0))
              {
                iVar3 = DfsPrimToCent(uVar17,2);
                iVar4 = DfsPrimToCent(param_4,2);
                if (iVar3 == iVar4) {
                  bVar5 = pbVar1[0x49c];
                }
                else {
                  local_74 = (uint)pbVar1[uVar12 * 0x14];
                  bVar5 = pbVar1[0x49c];
                  uVar14 = *(ushort *)(pbVar1 + uVar12 * 0x14 + 0xc);
                }
                uVar15 = (uint)bVar5;
                uVar7 = local_74;
                uVar13 = uVar14;
              }
            }
            local_74 = uVar7;
            uVar12 = uVar12 + 1 & 0xff;
            uVar14 = uVar13;
          } while (uVar12 < uVar15);
        }
      }
      if (DebugLevel < 1) {
        return local_74;
      }
      printk("[%s]:When no available Ch, new pDfsParam->band_bw[%d]: %d\n","DfsRandomSelectChannel",
             uVar8,*(undefined1 *)(iVar9 + 4));
    }
    if (0 < DebugLevel) {
      printk("[%s]:Currently no immediately available Channel. Choose Ch %d\n",
             "DfsRandomSelectChannel",local_74);
      return local_74;
    }
  }
  return local_74;
}

