// module: mt7915.ko
// function: mt_op_set_icap_start @ 0x258198
// size: 132 bytes
//

undefined4
mt_op_set_icap_start(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 extraout_r2;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    return 0x503;
  }
  iVar2 = hc_get_chip_ops(*(undefined4 *)(iVar1 + 0xa797a0));
  if (*(code **)(iVar2 + 0x188) == (code *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s : The function is not hooked !!\n","mt_op_set_icap_start",extraout_r2,DebugLevel,
             param_4);
    }
  }
  else {
    iVar1 = (**(code **)(iVar2 + 0x188))(iVar1,param_2);
    if (iVar1 != 0) {
      return 0x501;
    }
  }
  return 0;
}

