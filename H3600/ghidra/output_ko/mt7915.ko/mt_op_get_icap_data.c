// module: mt7915.ko
// function: mt_op_get_icap_data @ 0x2582b4
// size: 168 bytes
//

undefined4
mt_op_get_icap_data(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                   undefined4 param_5)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  code *pcVar4;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar2 = 0x503;
  }
  else {
    iVar3 = hc_get_chip_ops(*(undefined4 *)(iVar1 + 0xa797a0));
    pcVar4 = *(code **)(iVar3 + 0x198);
    if ((pcVar4 == (code *)0x0) && (pcVar4 = *(code **)(iVar3 + 0x194), pcVar4 == (code *)0x0)) {
      if (-1 < DebugLevel) {
        printk("%s : The function is not hooked !!\n","mt_op_get_icap_data");
      }
    }
    else {
      iVar1 = (*pcVar4)(iVar1,param_3,param_2,param_5,param_4);
      if (iVar1 != 0) {
        return 0x501;
      }
    }
    uVar2 = 0;
  }
  return uVar2;
}

