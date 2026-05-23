// module: mt7915.ko
// function: mt_ad_set_txbf_tx_apply @ 0x25d400
// size: 72 bytes
//

undefined4 mt_ad_set_txbf_tx_apply(int param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined4 uVar6;
  
  uVar1 = param_2[1];
  uVar2 = param_2[2];
  uVar3 = param_2[3];
  uVar4 = param_2[4];
  uVar5 = *param_2;
  uVar6 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  CmdTxBfTxApplyCtrl(uVar6,uVar5,uVar1,uVar2,uVar3,uVar4);
  return 0;
}

