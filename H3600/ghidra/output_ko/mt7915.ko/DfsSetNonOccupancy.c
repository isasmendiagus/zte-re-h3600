// module: mt7915.ko
// function: DfsSetNonOccupancy @ 0x232ad8
// size: 768 bytes
//

void DfsSetNonOccupancy(int param_1,undefined4 param_2,uint param_3,undefined4 param_4,char param_5)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  uint uVar6;
  byte *pbVar7;
  uint uVar8;
  
  pbVar2 = (byte *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  switch(param_4) {
  case 0:
    if (param_5 == '\0') {
      return;
    }
    bVar1 = pbVar2[0x49c];
    if (bVar1 == 0) {
      return;
    }
    pbVar5 = pbVar2;
    do {
      pbVar7 = pbVar5 + 0x14;
      if (*pbVar5 == param_3) {
        pbVar5[0xc] = 8;
        pbVar5[0xd] = 7;
        pbVar5[9] = 0;
      }
      pbVar5 = pbVar7;
    } while (pbVar7 != pbVar2 + ((byte)(bVar1 - 1) + 1) * 0x14);
    return;
  case 1:
    if (param_5 == '\0') {
      return;
    }
    if (pbVar2[0x49c] == 0) {
      return;
    }
    pbVar5 = pbVar2 + ((byte)(pbVar2[0x49c] - 1) + 1) * 0x14;
    break;
  case 2:
    if (param_5 == '\0') {
      return;
    }
    if (pbVar2[0x49c] == 0) {
      return;
    }
    uVar6 = 0;
    do {
      iVar3 = vht_cent_ch_freq(pbVar2[uVar6 * 0x14],1,1);
      uVar8 = uVar6 + 1 & 0xff;
      iVar4 = vht_cent_ch_freq(param_3,1,1);
      if (iVar3 == iVar4) {
        (pbVar2 + uVar6 * 0x14 + 0xc)[0] = 8;
        (pbVar2 + uVar6 * 0x14 + 0xc)[1] = 7;
        pbVar2[uVar6 * 0x14 + 9] = 2;
      }
      uVar6 = uVar8;
    } while (uVar8 < pbVar2[0x49c]);
    return;
  case 3:
    if ((*(uint *)(param_1 + 0x7953e0) & 0xffff00) == 0) {
      return;
    }
    if (pbVar2[0x49c] == 0) {
      return;
    }
    uVar6 = 0;
    do {
      iVar3 = vht_cent_ch_freq(pbVar2[uVar6 * 0x14],2,1);
      uVar8 = uVar6 + 1 & 0xff;
      iVar4 = vht_cent_ch_freq(*(undefined1 *)(param_1 + 0x795130),2,1);
      if (iVar3 == iVar4) {
        (pbVar2 + uVar6 * 0x14 + 0xc)[0] = 8;
        (pbVar2 + uVar6 * 0x14 + 0xc)[1] = 7;
        pbVar2[uVar6 * 0x14 + 9] = 3;
      }
      uVar6 = uVar8;
    } while (uVar8 < pbVar2[0x49c]);
  default:
    return;
  case 6:
    if ((*(char *)(param_1 + 0x7953e1) != '\0') && (*(char *)(param_1 + 0x7953e4) != '\0')) {
      if (pbVar2[0x49c] == 0) {
        return;
      }
      uVar6 = 0;
      do {
        iVar3 = vht_cent_ch_freq(pbVar2[uVar6 * 0x14],3,1);
        uVar8 = uVar6 + 1 & 0xff;
        iVar4 = vht_cent_ch_freq(*(undefined1 *)(param_1 + 0x795130),3,1);
        if (iVar3 == iVar4) {
          (pbVar2 + uVar6 * 0x14 + 0xc)[0] = 8;
          (pbVar2 + uVar6 * 0x14 + 0xc)[1] = 7;
          pbVar2[uVar6 * 0x14 + 9] = 6;
        }
        uVar6 = uVar8;
      } while (uVar8 < pbVar2[0x49c]);
      return;
    }
    if (*(char *)(param_1 + 0x7953e2) == '\0') {
      return;
    }
    if (*(char *)(param_1 + 0x7953e5) == '\0') {
      return;
    }
    if (pbVar2[0x49c] == 0) {
      return;
    }
    uVar6 = 0;
    do {
      iVar3 = vht_cent_ch_freq(pbVar2[uVar6 * 0x14],3,1);
      uVar8 = uVar6 + 1 & 0xff;
      iVar4 = vht_cent_ch_freq(*(undefined1 *)(param_1 + 0x795131),3,1);
      if (iVar3 == iVar4) {
        (pbVar2 + uVar6 * 0x14 + 0xc)[0] = 8;
        (pbVar2 + uVar6 * 0x14 + 0xc)[1] = 7;
        pbVar2[uVar6 * 0x14 + 9] = 6;
      }
      uVar6 = uVar8;
    } while (uVar8 < pbVar2[0x49c]);
    return;
  }
  do {
    uVar6 = (uint)*pbVar2;
    if (uVar6 == param_3) {
LAB_00232d64:
      pbVar2[0xc] = 8;
      pbVar2[0xd] = 7;
      pbVar2[9] = 1;
    }
    else {
      iVar3 = param_3 - uVar6;
      if ((int)(param_3 << 0x1d) < 0) {
        iVar3 = uVar6 - param_3;
      }
      if (iVar3 == 4) goto LAB_00232d64;
    }
    pbVar2 = pbVar2 + 0x14;
    if (pbVar2 == pbVar5) {
      return;
    }
  } while( true );
}

