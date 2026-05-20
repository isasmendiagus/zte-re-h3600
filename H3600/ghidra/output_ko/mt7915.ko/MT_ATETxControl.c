// module: mt7915.ko
// function: MT_ATETxControl @ 0x287948
// size: 592 bytes
//

undefined4 MT_ATETxControl(int param_1,uint param_2,int param_3)

{
  ushort uVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  if (*(int *)(param_1 + 0xa39fdc) == 1) {
    if (*(char *)(param_1 + 0xa3bafa) == '\0') {
      return 0;
    }
    if ((*(uint *)(param_1 + 0x286280) & 0xfffffffb) != 1) {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("Not supported in this interface yet\n");
      return 0;
    }
    complete(param_1 + 0xa77ba4);
    return 0;
  }
  if (*(int *)(param_1 + 0xa39fdc) != 0) {
    return 0;
  }
  if (param_3 != 0) {
    uVar4 = (uint)*(byte *)(param_3 + 0x2d);
    if ((0x67 < uVar4) || (iVar3 = *(int *)(param_1 + uVar4 * 4 + 0xc), iVar3 == 0)) {
      if (-1 < DebugLevel) {
        printk("%s: cannot find wdev by idx:%x\n","MT_ATEGetBandIdx",uVar4);
      }
      param_2 = 0xffffffff;
      goto joined_r0x00287a58;
    }
    param_2 = HcGetBandByChannel(param_1,*(undefined1 *)(iVar3 + 0x1a));
    if (3 < DebugLevel) {
      printk("%s: wdev_idx:%x\n","MT_ATEGetBandIdx",uVar4);
    }
  }
  if (param_2 < 2) {
    iVar3 = net_ad_wrap_service(param_1);
    iVar5 = param_2 * 0xd18;
    iVar6 = *(int *)(iVar3 + iVar5 + 0x111c);
    net_ad_wrap_service(param_1);
    iVar3 = net_ad_wrap_service(param_1);
    if ((*(uint *)(iVar3 + iVar5 + 0x4e0) & 2) == 0) {
      return 0;
    }
    if (param_3 != 0) {
      iVar3 = net_ad_wrap_service(param_1);
      uVar1 = *(ushort *)(iVar3 + iVar5 + 0x6f8);
      if (uVar1 < 0x100) {
        *(ushort *)(iVar3 + iVar5 + 0x6f8) = uVar1 + 1;
      }
      *(int *)(param_1 + 0xa39e6c) = *(int *)(param_1 + 0xa39e6c) + 1;
      iVar3 = net_ad_wrap_service(param_1);
      *(int *)(param_2 * 0xd18 + iVar3 + 0x111c) = iVar6 + 1;
    }
    _raw_spin_lock_bh(param_1 + 0xa3a044);
    if (*(char *)(param_1 + 0x79504d) == '\0') {
      param_2 = 0;
    }
    else {
      param_2 = param_2 & 1;
    }
    if (param_2 == 0) {
      bVar2 = 1;
    }
    else {
      bVar2 = 2;
    }
    *(byte *)(param_1 + 0xa3a050) = bVar2 | *(byte *)(param_1 + 0xa3a050);
    _raw_spin_unlock_bh(param_1 + 0xa3a044);
    RtmpOsTaskWakeUp(param_1 + 0xa3a014);
    return 0;
  }
joined_r0x00287a58:
  if (-1 < DebugLevel) {
    printk("%s: Wrong band_idx %u\n","MT_ATETxControl",param_2);
  }
  return 0;
}

