// module: mt7915.ko
// function: ctrl_fw_state_v2 @ 0x1bf9ec
// size: 424 bytes
//

int ctrl_fw_state_v2(int param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar2 = AsicGetFwSyncValue(param_1);
  switch(param_2) {
  case 0:
    if (uVar2 < 2) {
      return 0;
    }
    iVar1 = MtCmdRestartDLReq(param_1);
    if (iVar1 != 0) goto LAB_001bfaac;
    iVar1 = 0x5dd;
    do {
      uVar2 = AsicGetFwSyncValue(param_1);
      if (uVar2 < 2) {
        return 0;
      }
      RtmpOsMsDelay();
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    break;
  case 1:
  case 2:
    if (uVar2 == 1) {
      return 0;
    }
    if (((uVar2 != 0) && (iVar1 = MtCmdRestartDLReq(param_1), iVar1 != 0)) ||
       (iVar1 = MtCmdPowerOnWiFiSys(param_1), iVar1 != 0)) goto LAB_001bfaac;
    iVar1 = 0x5dd;
    do {
      uVar2 = AsicGetFwSyncValue(param_1);
      if (uVar2 == 1) {
        return 0;
      }
      RtmpOsMsDelay();
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    break;
  case 3:
    if ((*(uint *)(iVar1 + 0x100) & 2) == 0) {
      uVar3 = 3;
    }
    else {
      uVar3 = 7;
    }
    if (uVar3 == uVar2) {
      return 0;
    }
    iVar1 = 0x5dd;
    do {
      uVar2 = AsicGetFwSyncValue(param_1);
      if (uVar3 == uVar2) {
        return 0;
      }
      RtmpOsMsDelay(1);
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    break;
  default:
    if (DebugLevel < 1) {
      return 1;
    }
    printk("%s: invalid target stage\n","ctrl_fw_state_v2");
    iVar1 = 1;
    goto LAB_001bfaac;
  }
  iVar1 = 1;
LAB_001bfaac:
  if (0 < DebugLevel) {
    printk("%s: fail, target stage = %d, current sync CR = %d \n","ctrl_fw_state_v2",param_2,uVar2);
  }
  return iVar1;
}

