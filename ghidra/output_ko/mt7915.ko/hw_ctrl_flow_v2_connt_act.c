// module: mt7915.ko
// function: hw_ctrl_flow_v2_connt_act @ 0xb06c4
// size: 220 bytes
//

undefined4 hw_ctrl_flow_v2_connt_act(int *param_1)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar6 = *param_1;
  iVar5 = param_1[0x83];
  iVar4 = *(int *)(iVar6 + 8);
  iVar2 = hc_get_chip_cap(*(undefined4 *)(iVar4 + 0xa797a0));
  if ((*(char *)(iVar4 + 0x79504c) != '\0') ||
     (iVar3 = get_starec_by_wcid(iVar4,*(undefined2 *)((int)param_1 + 0x22)), iVar3 == 0)) {
    if (param_1[0xb] != 0) {
      AsicStaRecUpdate(iVar4,param_1 + 8);
    }
    wifi_sys_update_starec(iVar4,param_1 + 8);
    uVar1 = txop0;
    if (*(char *)(iVar4 + 0x795071) != '\0') {
      uVar1 = *(undefined2 *)(iVar2 + 0x226);
    }
    hw_set_tx_burst(iVar4,iVar6,2,0,uVar1,1);
  }
  if (iVar5 != 0) {
    os_free_mem(iVar5);
  }
  return 0;
}

