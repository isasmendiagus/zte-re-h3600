// module: mt7915.ko
// function: mt_op_set_mutb_spe @ 0x259364
// size: 96 bytes
//

undefined4 mt_op_set_mutb_spe(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar3 = param_4;
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 != 0) {
    iVar2 = hc_get_chip_dbg(*(undefined4 *)(iVar1 + 0xa797a0));
    if (*(code **)(iVar2 + 0xa0) != (code *)0x0) {
      (**(code **)(iVar2 + 0xa0))(iVar1,param_2,param_3,param_4,uVar3);
    }
    return 0;
  }
  return 0x503;
}

