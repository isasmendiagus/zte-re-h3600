// module: mt7915.ko
// function: WLAN_EXTENDER_Report_LinkUpDown_Event @ 0x15a344
// size: 96 bytes
//

void WLAN_EXTENDER_Report_LinkUpDown_Event(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_c;
  
  local_c = 1;
  if ((param_2 == 0) || (iVar1 = HcGetBandByWdev(), iVar1 != 0)) {
    local_c = 1;
  }
  else {
    local_c = 0;
  }
  Kernel_ASEND("cspd.cspconfig.wlan_config",param_3,&local_c,4,0,0);
  return;
}

