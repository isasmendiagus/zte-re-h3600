// module: mt7915.ko
// function: mt_op_set_slot_time @ 0x2575bc
// size: 96 bytes
//

undefined4
mt_op_set_slot_time(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                   undefined2 param_5,undefined1 param_6)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar2 = 0x503;
  }
  else {
    iVar1 = MtCmdATESetSlotTime(iVar1,param_2,param_3,param_4,param_5,param_6);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = 0x501;
    }
  }
  return uVar2;
}

