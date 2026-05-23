// module: mt7915.ko
// function: RTMPIoctlGetRadioStats @ 0xdcb90
// size: 372 bytes
//

void RTMPIoctlGetRadioStats(int *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  bool bVar7;
  undefined1 auStack_30 [4];
  uint local_2c [2];
  
  uVar5 = 0;
  local_2c[0] = 0;
  if (param_1 != (int *)0x0) {
    while( true ) {
      uVar6 = uVar5 & 0xffff;
      uVar1 = HcGetMaxStaNum(param_1);
      uVar5 = uVar5 + 1;
      if (uVar1 <= uVar6) break;
      if ((param_1[uVar6 * 0x530 + 0x28748] == 0x20001) && (param_2 != 0)) {
        get_wdev_by_ioctl_idx_and_iftype
                  (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
        iVar2 = HcGetBandByWdev();
        iVar3 = HcGetBandByWdev(param_1[uVar6 * 0x530 + 0x2874a]);
        if ((iVar2 == iVar3) && (param_1[uVar6 * 0x530 + 0x28787] == 2)) {
          uVar4 = param_1[uVar6 * 0x530 + 0x28c16];
          uVar1 = param_1[uVar6 * 0x530 + 0x28c17];
          bVar7 = uVar1 <= (uint)param_1[uVar6 * 0x530 + 0x28c0d];
          if (param_1[uVar6 * 0x530 + 0x28c0d] == uVar1) {
            bVar7 = uVar4 <= (uint)param_1[uVar6 * 0x530 + 0x28c0c];
          }
          if (bVar7) {
            uVar4 = param_1[uVar6 * 0x530 + 0x28c1a];
            uVar1 = local_2c[0];
          }
          if (bVar7) {
            local_2c[0] = uVar1 + uVar4;
          }
          bVar7 = (uint)param_1[uVar6 * 0x530 + 0x28c19] <= (uint)param_1[uVar6 * 0x530 + 0x28c0f];
          if (param_1[uVar6 * 0x530 + 0x28c0f] == param_1[uVar6 * 0x530 + 0x28c19]) {
            bVar7 = (uint)param_1[uVar6 * 0x530 + 0x28c18] <= (uint)param_1[uVar6 * 0x530 + 0x28c0e]
            ;
          }
          if (bVar7) {
            local_2c[0] = local_2c[0] + param_1[uVar6 * 0x530 + 0x28c1c];
          }
        }
      }
    }
    uVar5 = *(uint *)(param_2 + 0x10);
    *(undefined2 *)(param_2 + 0x14) = 4;
    uVar1 = *(uint *)(((uint)auStack_30 & 0xffffe000) + 8);
    if (uVar5 < 0xfffffffc && uVar5 + 4 <= uVar1) {
      uVar1 = 0;
    }
    if ((uVar1 == 0) && (iVar2 = __copy_to_user(uVar5,local_2c), iVar2 == 0)) {
      return;
    }
    if (-1 < DebugLevel) {
      printk("%s: copy_to_user() fail\n","RTMPIoctlGetRadioStats");
    }
  }
  return;
}

