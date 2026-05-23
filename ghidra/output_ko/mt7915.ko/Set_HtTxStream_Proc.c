// module: mt7915.ko
// function: Set_HtTxStream_Proc @ 0xde7e4
// size: 308 bytes
//

undefined4
Set_HtTxStream_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  
  iVar5 = *param_1;
  iVar7 = *(int *)(iVar5 + 0x3c);
  iVar5 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,iVar7,*(undefined4 *)(iVar5 + 0x38),iVar5,param_4);
  bVar1 = *(byte *)(param_1 + 0xa5b73) >> 4;
  if (iVar5 == 0) {
    return 0;
  }
  if (*(char *)((int)param_1 + 0x79504d) != '\0') {
    iVar3 = HcGetBandByWdev();
    if (iVar3 == 0) {
      bVar1 = *(byte *)((int)param_1 + 0x296dce);
    }
    else {
      bVar1 = *(byte *)(param_1 + 0xa5b74);
    }
  }
  uVar6 = (uint)bVar1;
  uVar2 = os_str_tol(param_2,0,10);
  if ((uVar2 != 0) && (uVar2 <= uVar6)) {
    uVar6 = uVar2 & 0xff;
  }
  wlan_config_set_tx_stream(iVar5,uVar6);
  wlan_operate_set_tx_stream(iVar5,uVar6);
  SetCommonHtVht(param_1,iVar5);
  if (*(char *)((int)param_1 + 0x286285) == '\x01') {
    APStop(param_1,param_1 + iVar7 * 0x160d + 0xadc92,1);
    APStartUp(param_1,param_1 + iVar7 * 0x160d + 0xadc92,1);
  }
  if (DebugLevel < 3) {
    return 1;
  }
  uVar4 = wlan_operate_get_tx_stream(iVar5);
  printk("Set_HtTxStream_Proc::(Tx Stream=%d)\n",uVar4);
  return 1;
}

