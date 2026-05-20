// module: mt7915.ko
// function: hw_ctrl_flow_v1_open @ 0xb0478
// size: 88 bytes
//

undefined4 hw_ctrl_flow_v1_open(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *param_1;
  uVar2 = *(undefined4 *)(iVar1 + 8);
  if (param_1[4] != 0) {
    AsicDevInfoUpdate(uVar2,(char)param_1[1],(int)param_1 + 5,*(undefined1 *)((int)param_1 + 0xb),
                      (char)param_1[3],param_1[4]);
    wifi_sys_update_devinfo(uVar2,iVar1,param_1 + 1);
  }
  return 0;
}

