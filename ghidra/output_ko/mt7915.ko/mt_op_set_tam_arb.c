// module: mt7915.ko
// function: mt_op_set_tam_arb @ 0x258dfc
// size: 48 bytes
//

undefined4 mt_op_set_tam_arb(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 != 0) {
    wifi_test_muru_set_arb_op_mode(iVar1,param_2);
    return 0;
  }
  return 0x503;
}

