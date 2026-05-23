// module: mt7915.ko
// function: mt_op_hetb_ctrl @ 0x2591d0
// size: 244 bytes
//

undefined4
mt_op_hetb_ctrl(int param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined1 param_5,
               undefined1 param_6,undefined1 param_7,byte param_8,int param_9)

{
  int iVar1;
  int iVar2;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    return 0x503;
  }
  iVar2 = hc_get_chip_dbg(*(undefined4 *)(iVar1 + 0xa797a0));
  if (param_3 == 3) {
    if (*(code **)(iVar2 + 0x9c) != (code *)0x0) {
      (**(code **)(iVar2 + 0x9c))
                (iVar1,param_2,param_4,param_5,param_6,param_7,0x60ff,0x240004,
                 param_9 + (uint)param_8 * 0x6c,param_9);
      return 0;
    }
  }
  else if (*(code **)(iVar2 + 0x98) != (code *)0x0) {
    (**(code **)(iVar2 + 0x98))(iVar1,param_2,param_3,param_5,param_6,param_7,param_9);
    return 0;
  }
  return 0x500;
}

