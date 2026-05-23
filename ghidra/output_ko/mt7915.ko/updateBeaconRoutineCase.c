// module: mt7915.ko
// function: updateBeaconRoutineCase @ 0xb5874
// size: 464 bytes
//

void updateBeaconRoutineCase(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  byte bVar7;
  char cVar8;
  int *piVar9;
  
  iVar1 = get_default_wdev();
  if (iVar1 == 0) {
    uVar3 = 0;
    uVar2 = 0;
  }
  else {
    uVar2 = wlan_config_get_ht_bw();
    uVar3 = wlan_config_get_ext_cha(iVar1);
    wlan_operate_get_ht_bw(iVar1);
    wlan_operate_get_ext_cha(iVar1);
  }
  cVar8 = (&DAT_0036b89f)[param_1];
  if (cVar8 == '\0') {
    cVar8 = (&DAT_0036b8a0)[param_1];
  }
  (&DAT_0036b89f)[param_1] = cVar8 + -1;
  iVar4 = QBSS_LoadIsAlarmIssued(param_1);
  if (((&DAT_0036b89f)[param_1] == '\0') &&
     (((bVar7 = *(byte *)(param_1 + 0x795652), (bVar7 & 2) != 0 &&
       (*(char *)(param_1 + 0x795947) == '\0')) || (iVar4 == 1)))) {
    if (2 < DebugLevel) {
      printk("DTIM Period reached, BSS20WidthReq=%d, Intolerant40=%d!\n",
             ((uint)*(byte *)(param_1 + 0x7956b4) << 0x1d) >> 0x1f,
             ((uint)*(byte *)(param_1 + 0x7956b4) << 0x1e) >> 0x1f);
      bVar7 = *(byte *)(param_1 + 0x795652);
    }
    bVar7 = bVar7 & 0xfd;
    *(byte *)(param_1 + 0x795652) = bVar7;
    if (iVar1 != 0) {
      uVar5 = wlan_operate_get_ht_bw(iVar1);
      uVar6 = wlan_operate_get_ext_cha(iVar1);
      if (((*(byte *)(param_1 + 0x7956b4) & 6) == 0) &&
         (*(char *)(param_1 + 0x285948) != '\x01' && iVar4 != 1)) {
        wlan_operate_set_ht_bw(iVar1,uVar2,uVar3);
      }
      else {
        wlan_operate_set_ht_bw(iVar1,0,0);
      }
      if (2 < DebugLevel) {
        uVar3 = wlan_operate_get_ht_bw(iVar1);
        uVar2 = wlan_operate_get_ext_cha(iVar1);
        printk("\tNow RecomWidth=%d, ExtChanOffset=%d, prevBW=%d, prevExtOffset=%d\n",uVar3,uVar2,
               uVar5,uVar6);
      }
      bVar7 = *(byte *)(param_1 + 0x795652);
    }
    *(byte *)(param_1 + 0x795652) = bVar7 | 4;
  }
  piVar9 = (int *)(param_1 + 8);
  do {
    piVar9 = piVar9 + 1;
    if (*piVar9 != 0) {
      MakeBeacon(param_1,*piVar9,param_2);
    }
  } while (piVar9 != (int *)(param_1 + 0x1a8));
  return;
}

