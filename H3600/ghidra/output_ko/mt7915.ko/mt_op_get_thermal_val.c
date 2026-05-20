// module: mt7915.ko
// function: mt_op_get_thermal_val @ 0x25865c
// size: 72 bytes
//

undefined4
mt_op_get_thermal_val(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = param_4;
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    return 0x503;
  }
  iVar1 = MtCmdGetThermalSensorResult(iVar1,0,param_3,param_4,uVar2);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = 0x501;
  }
  return uVar2;
}

