// module: mt7915.ko
// function: hw_ctrl_flow_v1_connt_act @ 0xb00d4
// size: 292 bytes
//

undefined4 hw_ctrl_flow_v1_connt_act(int *param_1)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  iVar7 = *param_1;
  iVar6 = param_1[0x83];
  iVar8 = param_1[0x3b];
  iVar5 = *(int *)(iVar7 + 8);
  iVar2 = hc_get_chip_cap(*(undefined4 *)(iVar5 + 0xa797a0));
  iVar3 = get_starec_by_wcid(iVar5,*(undefined2 *)((int)param_1 + 0x22));
  if (iVar3 == 0) {
    uVar4 = param_1[0xb];
    if ((uVar4 & 0xffffefff) != 0) {
      AsicUpdateRxWCIDTable(iVar5,*(undefined2 *)((int)param_1 + 0x22),iVar8 + 0xb,0,0);
      AsicStaRecUpdate(iVar5,param_1 + 8);
      uVar4 = param_1[0xb];
    }
    if ((uVar4 & 0x1000) != 0) {
      AsicAddRemoveKeyTab(iVar5,param_1 + 0xd);
    }
    wifi_sys_update_starec(iVar5,param_1 + 8);
    uVar1 = txop0;
    if (*(char *)(iVar5 + 0x795071) != '\0') {
      uVar1 = *(undefined2 *)(iVar2 + 0x226);
    }
    hw_set_tx_burst(iVar5,iVar7,2,0,uVar1,1);
  }
  else if ((param_1[0xb] & 0x1000U) != 0) {
    AsicAddRemoveKeyTab(iVar5,param_1 + 0xd);
  }
  if (iVar6 != 0) {
    os_free_mem(iVar6);
  }
  return 0;
}

