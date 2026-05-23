// module: mt7915.ko
// function: RTMPAPPrivIoctlGetChannelUtilization @ 0x1578dc
// size: 204 bytes
//

int RTMPAPPrivIoctlGetChannelUtilization(int *param_1,int param_2)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined8 uVar5;
  undefined1 auStack_18 [4];
  undefined4 local_14 [2];
  
  uVar5 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if ((int)uVar5 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = HcGetBandByWdev((int)uVar5,(int)((ulonglong)uVar5 >> 0x20));
  }
  local_14[0] = ZTE_Get_ChannelUtilization(param_1,uVar1);
  uVar2 = *(uint *)(param_2 + 0x10);
  uVar3 = *(uint *)(((uint)auStack_18 & 0xffffe000) + 8);
  if (uVar2 < 0xfffffffc && uVar2 + 4 <= uVar3) {
    uVar3 = 0;
  }
  if (uVar3 == 0) {
    iVar4 = __copy_to_user(uVar2,local_14,4);
    if (iVar4 == 0) {
      return 0;
    }
  }
  else {
    iVar4 = 4;
  }
  if (-1 < DebugLevel) {
    printk("RTMPAPPrivIoctlGetChannelUtilization uRet=%d\n",iVar4);
  }
  return iVar4;
}

