// module: mt7915.ko
// function: hw_ctrl_flow_v1_disconnt_act @ 0xaffe0
// size: 244 bytes
//

undefined4 hw_ctrl_flow_v1_disconnt_act(int *param_1)

{
  char cVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  
  iVar5 = *param_1;
  uVar6 = *(undefined4 *)(iVar5 + 8);
  if ((param_1[0xb] & 0xffffefffU) != 0) {
    AsicStaRecUpdate(uVar6,param_1 + 8);
  }
  uVar2 = *(ushort *)((int)param_1 + 0x22);
  uVar3 = HcGetMaxStaNum(uVar6);
  if ((uVar2 < uVar3) || (*(short *)((int)param_1 + 0x22) == 0x7fff)) {
    AsicDelWcidTab(uVar6);
    cVar1 = (char)param_1[0x84];
  }
  else {
    cVar1 = (char)param_1[0x84];
  }
  if (cVar1 == '\0') {
    hw_set_tx_burst(uVar6,iVar5,2,0,txop0,0);
  }
  wifi_sys_update_starec(uVar6,param_1 + 8);
  if (*(int *)(iVar5 + 0x14) == 1) {
    iVar4 = wlan_operate_get_addht(iVar5);
    *(undefined4 *)(iVar5 + 0x8dc) = 0;
    *(byte *)(iVar4 + 2) = *(byte *)(iVar4 + 2) & 0xfc;
    UpdateBeaconHandler(uVar6,iVar5,2);
  }
  return 0;
}

