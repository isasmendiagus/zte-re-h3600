// module: mt7915.ko
// function: DfsCheckBwGroupAllAvailable @ 0x232610
// size: 380 bytes
//

undefined4 DfsCheckBwGroupAllAvailable(uint param_1,uint param_2,int param_3,int param_4)

{
  byte bVar1;
  int iVar2;
  uint extraout_r1;
  int iVar3;
  byte *pbVar4;
  byte bVar5;
  int iVar6;
  byte *pbVar7;
  int iVar8;
  
  iVar2 = hc_get_channel_ctrl(*(undefined4 *)(param_3 + 0xa797a0),param_4);
  if (param_2 != 0) {
    if (param_2 == 1) {
      bVar1 = 0x1e;
      iVar8 = 2;
      pbVar7 = (byte *)(param_3 + param_4 * 0xda + 0x7951af);
    }
    else if (param_2 == 2) {
      bVar1 = 0x24;
      iVar8 = 4;
      pbVar7 = (byte *)(param_3 + param_4 * 0xda + 0x7951cd);
    }
    else {
      if (param_2 != 3) {
        return 0;
      }
      bVar1 = 0x20;
      iVar8 = 8;
      pbVar7 = (byte *)(param_3 + param_4 * 0xda + 0x7951f1);
    }
    if (*pbVar7 == param_1) {
      iVar3 = 0;
    }
    else {
      bVar5 = 0;
      do {
        pbVar7 = pbVar7 + 1;
        bVar5 = bVar5 + 1;
        if (bVar1 <= bVar5) {
          return 0;
        }
      } while (*pbVar7 != param_1);
      __aeabi_uidivmod(bVar5,iVar8);
      iVar3 = -(extraout_r1 & 0xff);
    }
    pbVar4 = pbVar7 + iVar3 + -1;
    do {
      pbVar4 = pbVar4 + 1;
      iVar6 = iVar2 + (uint)*pbVar4 * 0x14;
      if (*(short *)(iVar6 + 0xc) != 0) {
        return 0;
      }
      if ((*(char *)(iVar6 + 7) != '\0') && (*(byte *)(iVar6 + 9) <= param_2)) {
        return 0;
      }
    } while (pbVar4 != pbVar7 + (iVar8 - 1U & 0xff) + iVar3);
  }
  return 1;
}

