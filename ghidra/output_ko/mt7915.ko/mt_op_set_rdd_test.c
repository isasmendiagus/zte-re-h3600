// module: mt7915.ko
// function: mt_op_set_rdd_test @ 0x2586a4
// size: 112 bytes
//

undefined4 mt_op_set_rdd_test(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  printk("%s: rdd_idx: %d, rdd_sel: %d, enable:%d\n","mt_op_set_rdd_test",param_2,param_3,param_4);
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar2 = 0x503;
  }
  else {
    iVar1 = MtCmdSetRDDTestExt(iVar1,param_2,param_3,param_4);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = 0x501;
    }
  }
  return uVar2;
}

