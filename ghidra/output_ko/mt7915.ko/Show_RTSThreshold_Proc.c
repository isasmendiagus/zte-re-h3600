// module: mt7915.ko
// function: Show_RTSThreshold_Proc @ 0xd6354
// size: 96 bytes
//

undefined4 Show_RTSThreshold_Proc(int *param_1,char *param_2,size_t param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar1 != 0) {
    uVar2 = wlan_config_get_rts_len_thld();
    uVar3 = wlan_operate_get_rts_len_thld(iVar1);
    snprintf(param_2,param_3,"\tRTSThreshold:: conf=%d, oper=%d",uVar2,uVar3);
  }
  return 0;
}

