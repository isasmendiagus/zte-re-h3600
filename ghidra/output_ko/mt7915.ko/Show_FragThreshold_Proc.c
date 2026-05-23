// module: mt7915.ko
// function: Show_FragThreshold_Proc @ 0xd63b4
// size: 96 bytes
//

undefined4 Show_FragThreshold_Proc(int *param_1,char *param_2,size_t param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar1 != 0) {
    uVar2 = wlan_config_get_frag_thld();
    uVar3 = wlan_operate_get_frag_thld(iVar1);
    snprintf(param_2,param_3,"\tFrag thld:: conf=%u, oper=%u",uVar2,uVar3);
  }
  return 0;
}

