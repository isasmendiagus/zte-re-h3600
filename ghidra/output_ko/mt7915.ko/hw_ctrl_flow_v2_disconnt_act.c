// module: mt7915.ko
// function: hw_ctrl_flow_v2_disconnt_act @ 0xb0608
// size: 188 bytes
//

undefined4 hw_ctrl_flow_v2_disconnt_act(int *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = *param_1;
  uVar3 = *(undefined4 *)(iVar2 + 8);
  if (param_1[0xb] != 0) {
    AsicStaRecUpdate(uVar3,param_1 + 8);
  }
  if ((char)param_1[0x84] == '\0') {
    hw_set_tx_burst(uVar3,iVar2,2,0,txop0,0);
  }
  wifi_sys_update_starec(uVar3,param_1 + 8);
  if (*(int *)(iVar2 + 0x14) == 1) {
    iVar1 = wlan_operate_get_addht(iVar2);
    *(undefined4 *)(iVar2 + 0x8dc) = 0;
    *(byte *)(iVar1 + 2) = *(byte *)(iVar1 + 2) & 0xfc;
    UpdateBeaconHandler(uVar3,iVar2,2);
  }
  return 0;
}

