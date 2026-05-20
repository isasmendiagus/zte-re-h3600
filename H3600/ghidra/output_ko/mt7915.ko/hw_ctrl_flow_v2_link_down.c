// module: mt7915.ko
// function: hw_ctrl_flow_v2_link_down @ 0xb07a0
// size: 172 bytes
//

undefined4 hw_ctrl_flow_v2_link_down(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *param_1;
  uVar2 = *(undefined4 *)(iVar1 + 8);
  if (param_1[0xb] != 0) {
    AsicStaRecUpdate(uVar2,param_1 + 8);
    wifi_sys_update_starec(uVar2,param_1 + 8);
  }
  if ((char)param_1[0x84] == '\0') {
    hw_set_tx_burst(uVar2,iVar1,2,0,txop0,0);
  }
  if (param_1[0x4d] != 0) {
    AsicBssInfoUpdate(uVar2,param_1 + 0x3e);
    wifi_sys_update_bssinfo(uVar2,iVar1,param_1 + 0x3e);
  }
  return 0;
}

