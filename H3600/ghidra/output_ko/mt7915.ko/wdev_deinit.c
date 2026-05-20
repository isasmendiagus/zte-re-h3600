// module: mt7915.ko
// function: wdev_deinit @ 0x14de08
// size: 68 bytes
//

undefined4 wdev_deinit(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined4 uVar1;
  int iVar2;
  int extraout_r3;
  
  deinit_vie_ctrl(param_2);
  iVar2 = *(int *)(param_2 + 0x14);
  uVar1 = extraout_r2;
  if (iVar2 != 0x100) {
    wlan_operate_exit(param_2);
    hc_obj_exit(param_2);
    iVar2 = extraout_r3;
    uVar1 = extraout_r2_00;
  }
  wdev_idx_unreg(param_1,param_2,uVar1,iVar2,param_4);
  return 1;
}

