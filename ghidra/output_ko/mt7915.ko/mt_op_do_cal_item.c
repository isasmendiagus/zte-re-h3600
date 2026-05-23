// module: mt7915.ko
// function: mt_op_do_cal_item @ 0x2597ac
// size: 148 bytes
//

undefined4 mt_op_do_cal_item(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    return 0x503;
  }
  if (param_2 != 0) {
    if (param_2 == 0x2000000) {
      iVar1 = mt_op_set_test_mode_dnlk_2g(param_1);
    }
    else if (param_2 == 0x4000000) {
      iVar1 = mt_op_set_test_mode_dnlk_5g(param_1);
    }
    else {
      iVar1 = MtCmdDoCalibration(iVar1,1,param_2,param_3);
    }
    uVar2 = 0x501;
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    return uVar2;
  }
  printk("%s: Wrong input [%d] ! Check !\n","mt_op_do_cal_item",0);
  return 0x501;
}

