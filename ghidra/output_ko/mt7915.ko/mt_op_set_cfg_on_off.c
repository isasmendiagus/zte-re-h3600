// module: mt7915.ko
// function: mt_op_set_cfg_on_off @ 0x257464
// size: 76 bytes
//

undefined4
mt_op_set_cfg_on_off(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    return 0x503;
  }
  iVar1 = MtCmdCfgOnOff(iVar1,param_2,param_3,param_4);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = 0x501;
  }
  return uVar2;
}

