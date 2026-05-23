// module: mt7915.ko
// function: bss_coex_insert_effected_ch_list @ 0x110404
// size: 508 bytes
//

undefined4 bss_coex_insert_effected_ch_list(int param_1,uint param_2,int param_3,undefined4 param_4)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  byte bVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  undefined1 auStack_33 [4];
  byte local_2f;
  
  if ((*(char *)(param_1 + 0x795941) != '\x01') &&
     (iVar2 = scan_in_run_state(param_1,param_4), iVar2 == 0)) {
    return 0;
  }
  hc_radio_query_by_channel(param_1,param_2,auStack_33);
  uVar3 = HcGetBandByChannel(param_1,param_2);
  iVar2 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar3);
  if (0xe < param_2) {
    return 0;
  }
  uVar9 = (uint)*(byte *)(iVar2 + 0x49c);
  if (uVar9 == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = 0;
    iVar7 = 1;
    iVar8 = iVar2;
    do {
      while (*(char *)(iVar2 + iVar7 * 0x14 + -0x14) == *(char *)(param_3 + 0x30)) {
        if ((*(uint *)(param_3 + 0xa8) & 3) != 3) {
          *(byte *)(iVar8 + 1) = *(byte *)(iVar8 + 1) | 4;
          AddBssCoexApCnt(param_1,*(undefined1 *)(param_3 + 0x30),param_3 + 6);
          uVar9 = (uint)*(byte *)(iVar2 + 0x49c);
          uVar3 = 1;
          break;
        }
        *(byte *)(iVar8 + 1) = *(byte *)(iVar8 + 1) | 2;
        uVar4 = (uint)*(byte *)(param_3 + 0x30);
        bVar5 = *(byte *)(param_3 + 0xf7) & 3;
        if (bVar5 == 3) {
          if (uVar4 < 0xf) {
            if (iVar7 - 1U < 4) goto LAB_00110504;
            iVar6 = iVar7 + -5;
LAB_0011059c:
            iVar6 = iVar2 + iVar6 * 0x14;
            *(byte *)(iVar6 + 1) = *(byte *)(iVar6 + 1) | 1;
            uVar4 = (uint)*(byte *)(param_3 + 0x30);
            goto LAB_00110504;
          }
          if (iVar7 != 1) {
            iVar6 = iVar7 + -2;
            goto LAB_0011059c;
          }
LAB_00110520:
          AddBssCoexApCnt(param_1,uVar4,param_3 + 6);
          uVar3 = 1;
        }
        else {
          if (bVar5 == 1) {
            if (uVar4 < 0xf) {
              iVar6 = iVar7 + 3;
              if ((int)uVar9 <= iVar6) goto LAB_00110504;
            }
            else {
              iVar6 = iVar7;
              if ((int)uVar9 <= iVar7) goto LAB_00110520;
            }
            goto LAB_0011059c;
          }
LAB_00110504:
          if ((param_2 != uVar4) || ((*(byte *)(param_3 + 0xf7) & 3) != local_2f))
          goto LAB_00110520;
        }
        uVar9 = (uint)*(byte *)(iVar2 + 0x49c);
        iVar8 = iVar8 + 0x14;
        bVar1 = (int)uVar9 <= iVar7;
        iVar7 = iVar7 + 1;
        if (bVar1) {
          return uVar3;
        }
      }
      iVar8 = iVar8 + 0x14;
      bVar1 = iVar7 < (int)uVar9;
      iVar7 = iVar7 + 1;
    } while (bVar1);
  }
  return uVar3;
}

