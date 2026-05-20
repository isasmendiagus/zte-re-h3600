// module: mt7915.ko
// function: hw_ctrl_flow_v1_link_down @ 0xb01f8
// size: 184 bytes
//

undefined4 hw_ctrl_flow_v1_link_down(int *param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *param_1;
  uVar1 = *(undefined4 *)(iVar2 + 8);
  if ((param_1[0xb] & 0xffffefffU) != 0) {
    AsicStaRecUpdate(uVar1,param_1 + 8);
    AsicDelWcidTab(uVar1,*(undefined2 *)((int)param_1 + 0x22));
    wifi_sys_update_starec(uVar1,param_1 + 8);
  }
  if ((char)param_1[0x84] == '\0') {
    hw_set_tx_burst(uVar1,iVar2,2,0,txop0,0);
  }
  if (param_1[0x4d] != 0) {
    AsicBssInfoUpdate(uVar1,param_1 + 0x3e);
    wifi_sys_update_bssinfo(uVar1,iVar2,param_1 + 0x3e);
  }
  return 0;
}

