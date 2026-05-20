// module: mt7915.ko
// function: mt_op_get_icap_status @ 0x258220
// size: 128 bytes
//

undefined4
mt_op_get_icap_status(int param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 extraout_r2;
  undefined4 uVar4;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar4 = 0x503;
  }
  else {
    iVar2 = hc_get_chip_ops(*(undefined4 *)(iVar1 + 0xa797a0));
    if (*(code **)(iVar2 + 0x18c) == (code *)0x0) {
      if (DebugLevel < 0) {
        uVar4 = 0x501;
      }
      else {
        printk("%s : The function is not hooked !!\n","mt_op_get_icap_status",extraout_r2,DebugLevel
               ,param_4);
        uVar4 = 0x501;
      }
    }
    else {
      uVar3 = (**(code **)(iVar2 + 0x18c))(iVar1);
      uVar4 = 0;
      *param_2 = uVar3;
    }
  }
  return uVar4;
}

