// module: mt7915.ko
// function: net_ad_tx_pkt_handle @ 0x25a490
// size: 40 bytes
//

undefined4 net_ad_tx_pkt_handle(undefined4 param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  
  if (param_2 != 0) {
                    /* WARNING: Could not recover jumptable at 0x0025a4a0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(*(int *)(param_2 + 0x904) + 0x30))();
    return uVar1;
  }
  RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_3 + 0xc));
  return 1;
}

