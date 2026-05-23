// module: mt7915.ko
// function: ZTE_Get_CurrentBandWidth @ 0x1572f4
// size: 264 bytes
//

void ZTE_Get_CurrentBandWidth(int *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined1 auStack_18 [4];
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar1 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: get_wdev fail\n","ZTE_Get_CurrentBandWidth");
    }
  }
  else {
    if (((*(ushort *)(iVar1 + 0x18) & 0xb1) == 0) || (iVar3 = wlan_operate_get_vht_bw(), iVar3 != 1)
       ) {
      iVar1 = wlan_operate_get_ht_bw(iVar1);
      if (iVar1 == 1) {
        local_14[0] = 1;
      }
      else {
        local_14[0] = 0;
      }
    }
    else {
      local_14[0] = 3;
    }
    uVar2 = *(uint *)(param_2 + 0x10);
    *(undefined2 *)(param_2 + 0x14) = 4;
    uVar4 = *(uint *)(((uint)auStack_18 & 0xffffe000) + 8);
    if (uVar2 < 0xfffffffc && uVar2 + 4 <= uVar4) {
      uVar4 = 0;
    }
    if ((uVar4 == 0) && (iVar1 = __copy_to_user(uVar2,local_14), iVar1 == 0)) {
      return;
    }
    if (-1 < DebugLevel) {
      printk("%s: copy_to_user() fail\n","ZTE_Get_CurrentBandWidth");
    }
  }
  return;
}

