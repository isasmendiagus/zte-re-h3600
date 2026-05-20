// module: mt7915.ko
// function: wlan_operate_set_ht_bw @ 0x107a54
// size: 336 bytes
//

undefined4 wlan_operate_set_ht_bw(int param_1,uint param_2,uint param_3)

{
  char cVar1;
  char cVar2;
  uint uVar3;
  undefined1 *extraout_r1;
  undefined1 *puVar4;
  undefined1 *extraout_r1_00;
  int iVar5;
  int iVar6;
  int *piVar7;
  undefined4 uVar8;
  undefined8 uVar9;
  undefined1 uStack_32;
  undefined1 local_31;
  undefined1 local_2f;
  undefined1 auStack_29 [3];
  char local_26;
  
  uVar3 = wlan_config_get_ht_bw();
  if (((param_1 != 0) && (iVar6 = *(int *)(param_1 + 0xb14), iVar6 != 0)) &&
     ((*(byte *)(iVar6 + 9) != param_2 || (*(byte *)(iVar6 + 8) != param_3)))) {
    if (uVar3 < param_2) {
      if (DebugLevel < 0) {
        uVar8 = 0xffffffff;
      }
      else {
        uVar8 = 0xffffffff;
        printk("%s(): new ht_bw:%d > cap_ht_bw: %d, correct to cap_ht_bw\n","wlan_operate_set_ht_bw"
               ,param_2);
      }
    }
    else {
      uVar8 = 0;
      uVar3 = param_2;
    }
    phy_freq_get_cfg(param_1,&uStack_32);
    local_31 = (undefined1)uVar3;
    local_2f = (undefined1)param_3;
    operate_loader_phy(param_1,&uStack_32);
    cVar1 = *(char *)(iVar6 + 8);
    if (cVar1 != '\0') {
      iVar6 = *(int *)(param_1 + 8);
      piVar7 = (int *)(iVar6 + 8);
      puVar4 = extraout_r1;
      do {
        piVar7 = piVar7 + 1;
        iVar5 = *piVar7;
        if ((iVar5 != 0) && (*(char *)(iVar5 + 0x1a) == *(char *)(param_1 + 0x1a))) {
          uVar9 = wlan_operate_get_state(iVar5,puVar4);
          puVar4 = (undefined1 *)((ulonglong)uVar9 >> 0x20);
          if (((int)uVar9 == 1) &&
             (puVar4 = auStack_29, cVar2 = *(char *)(*(int *)(iVar5 + 0xb14) + 8),
             cVar2 != '\0' && cVar1 != cVar2)) {
            phy_freq_get_cfg(iVar5);
            local_26 = cVar1;
            operate_loader_phy(iVar5,auStack_29);
            puVar4 = extraout_r1_00;
          }
        }
      } while (piVar7 != (int *)(iVar6 + 0x1a8));
    }
    return uVar8;
  }
  return 0;
}

