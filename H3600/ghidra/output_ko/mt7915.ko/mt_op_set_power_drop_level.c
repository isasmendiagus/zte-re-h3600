// module: mt7915.ko
// function: mt_op_set_power_drop_level @ 0x25761c
// size: 68 bytes
//

undefined4 mt_op_set_power_drop_level(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    return 0x503;
  }
  iVar1 = MtCmdATESetPowerDropLevel(iVar1,param_2,param_3);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = 0x501;
  }
  return uVar2;
}

