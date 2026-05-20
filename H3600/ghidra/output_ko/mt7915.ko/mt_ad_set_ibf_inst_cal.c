// module: mt7915.ko
// function: mt_ad_set_ibf_inst_cal @ 0x25d530
// size: 60 bytes
//

void mt_ad_set_ibf_inst_cal(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  uVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  CmdITxBfPhaseCal(uVar1,param_2,param_3,param_4);
  return;
}

