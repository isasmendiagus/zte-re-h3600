// module: mt7915.ko
// function: mt_op_get_wf_path_comb @ 0x259178
// size: 88 bytes
//

undefined4
mt_op_get_wf_path_comb
          (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar2 = 0x503;
  }
  else {
    iVar1 = chip_get_wf_path_comb(iVar1,param_2,param_3,param_4,param_5);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = 0x501;
    }
  }
  return uVar2;
}

