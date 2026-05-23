// module: mt7915.ko
// function: GetBssCoexEffectedChRange @ 0x15ae0
// size: 804 bytes
//

undefined4 GetBssCoexEffectedChRange(int param_1,undefined4 param_2,char *param_3,uint param_4)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  byte *pbVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  char cVar8;
  byte *pbVar9;
  uint uVar10;
  
  iVar2 = wlan_operate_get_ext_cha(param_2);
  uVar3 = HcGetBandByWdev(param_2);
  pbVar4 = (byte *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar3);
  __memzero(param_3,4);
  if (0xe < param_4) {
    if (pbVar4[0x49c] == 0) {
LAB_00015bd0:
      if (DebugLevel < 0) {
        return 0;
      }
      printk("5GHz: Cannot found the CtrlCh(%d) in ChList, something wrong?\n",param_4);
      return 0;
    }
    if (*pbVar4 == param_4) {
      uVar5 = 0;
    }
    else {
      uVar5 = 0;
      pbVar9 = pbVar4;
      do {
        uVar5 = uVar5 + 1;
        if (uVar5 == pbVar4[0x49c]) goto LAB_00015bd0;
        pbVar9 = pbVar9 + 0x14;
      } while (*pbVar9 != param_4);
    }
    cVar8 = (char)param_4;
    *param_3 = cVar8;
    if (iVar2 == 1) {
      param_3[2] = cVar8;
      param_3[3] = cVar8 + '\x04';
      param_3[1] = cVar8 + '\x04';
      if (DebugLevel < 3) {
        return 1;
      }
      pcVar7 = "ABOVE";
    }
    else {
      param_3[3] = cVar8;
      param_3[2] = cVar8 + -4;
      param_3[1] = cVar8 + -4;
      if (DebugLevel < 3) {
        return 1;
      }
      pcVar7 = "BELOW";
    }
    printk("5.0GHz: Found CtrlCh idx(%d) from the ChList, ExtCh=%s, PriCh=[Idx:%d, CH:%d], SecCh=[Idx:%d, CH:%d], effected Ch=[CH:%d~CH:%d]!\n"
           ,uVar5,pcVar7,param_4,pbVar4[param_4 * 0x14],(uint)(byte)param_3[1],
           pbVar4[(uint)(byte)param_3[1] * 0x14],pbVar4[(uint)(byte)param_3[2] * 0x14],
           pbVar4[(uint)(byte)param_3[3] * 0x14]);
    return 1;
  }
  uVar5 = (uint)pbVar4[0x49c];
  if (uVar5 == 0) {
LAB_00015b74:
    if (DebugLevel < 0) {
      return 0;
    }
    printk("2.4GHz: Didn\'t found valid channel range, Ch index=%d, ChListNum=%d, CtrlCh=%d\n",uVar5
           ,uVar5,param_4);
    return 0;
  }
  if (*pbVar4 == param_4) {
    cVar8 = '\0';
    *param_3 = '\0';
    if (iVar2 != 1) {
      return 1;
    }
    uVar10 = 0;
  }
  else {
    pbVar9 = pbVar4;
    uVar10 = 0;
    do {
      uVar6 = uVar10;
      uVar10 = uVar6 + 1;
      if (uVar10 == uVar5) goto LAB_00015b74;
      pbVar9 = pbVar9 + 0x14;
    } while (*pbVar9 != param_4);
    cVar8 = (char)uVar10;
    *param_3 = cVar8;
    if (iVar2 != 1) {
      if ((int)(uVar6 - 3) < 0) {
        return 1;
      }
      param_3[1] = cVar8 + -4;
      if (uVar10 == 2) {
        return 1;
      }
      uVar5 = uVar6 + 4;
      uVar6 = uVar6 - 6 & ~((int)(uVar6 - 6) >> 0x1f);
      param_3[2] = (char)uVar6;
      param_3[3] = (char)uVar5;
      if (DebugLevel < 3) {
        return 1;
      }
      uVar1 = 0x8420;
      goto LAB_00015d90;
    }
  }
  if ((int)(uint)pbVar4[0x49c] <= (int)(uVar10 + 4)) {
    return 1;
  }
  uVar5 = uVar10 + 7;
  param_3[1] = cVar8 + '\x04';
  uVar6 = uVar10 - 3 & ~((int)(uVar10 - 3) >> 0x1f);
  param_3[2] = (char)uVar6;
  param_3[3] = (char)uVar5;
  if (DebugLevel < 3) {
    return 1;
  }
  uVar1 = 0x8428;
LAB_00015d90:
  printk("2.4GHz: Found CtrlCh idx(%d) from the ChList, ExtCh=%s, PriCh=[Idx:%d, CH:%d], SecCh=[Idx:%d, CH:%d], effected Ch=[CH:%d~CH:%d]!\n"
         ,uVar10,uVar1 | 0x2a0000,uVar10,pbVar4[uVar10 * 0x14],(uint)(byte)param_3[1],
         pbVar4[(uint)(byte)param_3[1] * 0x14],pbVar4[uVar6 * 0x14],pbVar4[(uVar5 & 0xff) * 0x14]);
  return 1;
}

