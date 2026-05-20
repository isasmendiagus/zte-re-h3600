// module: mt7915.ko
// function: hw_ctrl_flow_v2_link_up @ 0xb084c
// size: 284 bytes
//

undefined4 hw_ctrl_flow_v2_link_up(int *param_1)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = *param_1;
  iVar4 = *(int *)(iVar5 + 8);
  iVar2 = hc_get_chip_cap(*(undefined4 *)(iVar4 + 0xa797a0));
  if (param_1[0x4d] == 0) {
    iVar3 = param_1[0xb];
  }
  else {
    AsicBssInfoUpdate(iVar4,param_1 + 0x3e);
    HcSetEdca(iVar5);
    wifi_sys_update_bssinfo(iVar4,iVar5,param_1 + 0x3e);
    iVar3 = param_1[0xb];
  }
  if (iVar3 != 0) {
    AsicStaRecUpdate(iVar4,param_1 + 8);
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

