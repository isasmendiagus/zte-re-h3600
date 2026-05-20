// module: mt7915.ko
// function: mt_op_get_tx_pwr @ 0x258378
// size: 100 bytes
//

undefined4
mt_op_get_tx_pwr(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined1 param_5,uint *param_6)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 uStack_14;
  byte local_13;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar2 = 0x503;
  }
  else {
    iVar1 = MtCmdGetTxPower(iVar1,param_3,param_4,param_5,&uStack_14);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = 0x501;
    }
    *param_6 = (uint)local_13;
  }
  return uVar2;
}

