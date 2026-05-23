// module: mt7915.ko
// function: hw_ctrl_flow_v1_link_up @ 0xb02b0
// size: 368 bytes
//

undefined4 hw_ctrl_flow_v1_link_up(int *param_1)

{
  undefined2 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar5 = *param_1;
  iVar6 = param_1[0x3b];
  iVar4 = *(int *)(iVar5 + 8);
  iVar2 = hc_get_chip_cap(*(undefined4 *)(iVar4 + 0xa797a0));
  if (param_1[0x4d] == 0) {
    uVar3 = param_1[0xb];
  }
  else {
    AsicBssInfoUpdate(iVar4,param_1 + 0x3e);
    HcSetEdca(iVar5);
    wifi_sys_update_bssinfo(iVar4,iVar5,param_1 + 0x3e);
    uVar3 = param_1[0xb];
  }
  if ((uVar3 & 0xffffefff) != 0) {
    AsicUpdateRxWCIDTable(iVar4,*(undefined2 *)((int)param_1 + 0x22),iVar6 + 0xb,1,0);
    AsicStaRecUpdate(iVar4,param_1 + 8);
    uVar3 = param_1[0xb];
  }
  if ((uVar3 & 0x1000) != 0) {
    AsicAddRemoveKeyTab(iVar4,param_1 + 0xd);
    uVar3 = param_1[0xb];
  }
  if (uVar3 != 0) {
    wifi_sys_update_starec(iVar4,param_1 + 8);
  }
  uVar1 = txop0;
  if (*(char *)(iVar4 + 0x795071) != '\0') {
    uVar1 = *(undefined2 *)(iVar2 + 0x226);
  }
  hw_set_tx_burst(iVar4,iVar5,2,0,uVar1,1);
  iVar2 = *(int *)(iVar5 + 0x14);
  if ((iVar2 - 0x10U & 0xffffffef) == 0 || (iVar2 == 1 || iVar2 == 4)) {
    UpdateBeaconHandler(iVar4,iVar5,0);
  }
  return 0;
}

