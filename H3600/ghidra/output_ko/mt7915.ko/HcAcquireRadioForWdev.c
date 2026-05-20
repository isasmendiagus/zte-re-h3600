// module: mt7915.ko
// function: HcAcquireRadioForWdev @ 0xa8afc
// size: 200 bytes
//

undefined4 HcAcquireRadioForWdev(int param_1,int param_2)

{
  undefined1 uVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  
  uVar6 = *(undefined4 *)(param_1 + 0xa797a0);
  iVar5 = *(int *)(param_2 + 0xabc);
  greenap_suspend(param_1,4);
  uVar6 = RcAcquiredBandForObj
                    (uVar6,iVar5,*(undefined1 *)(param_2 + 0xc),*(undefined2 *)(param_2 + 0x18),
                     *(undefined1 *)(param_2 + 0x1a),*(undefined2 *)(param_2 + 0x14));
  uVar2 = *(undefined2 *)(param_2 + 0x18);
  uVar3 = RcGetPhyMode();
  iVar4 = wmode_band_equal(uVar2,uVar3);
  if (iVar4 == 0) {
    uVar2 = RcGetPhyMode(uVar6);
    *(undefined2 *)(param_2 + 0x18) = uVar2;
    uVar1 = RcGetChannel(uVar6);
    *(undefined1 *)(param_2 + 0x1a) = uVar1;
  }
  BuildChannelList(param_1,param_2);
  *(undefined1 *)(param_2 + 0x29) = *(undefined1 *)(iVar5 + 4);
  UpdateDot11hForWdev(*(undefined4 *)(param_2 + 8),param_2,1);
  wlan_operate_init(param_2);
  greenap_resume(param_1,4);
  return 0;
}

