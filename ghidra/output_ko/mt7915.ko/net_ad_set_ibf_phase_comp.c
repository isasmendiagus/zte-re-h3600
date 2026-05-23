// module: mt7915.ko
// function: net_ad_set_ibf_phase_comp @ 0x25d464
// size: 68 bytes
//

void net_ad_set_ibf_phase_comp(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  uVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  CmdITxBfPhaseComp(uVar1,param_2,param_3,param_4);
  return;
}

