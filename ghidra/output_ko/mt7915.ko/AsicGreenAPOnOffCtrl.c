// module: mt7915.ko
// function: AsicGreenAPOnOffCtrl @ 0x134eb8
// size: 96 bytes
//

undefined4 AsicGreenAPOnOffCtrl(int param_1,undefined1 param_2,undefined1 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined2 local_12;
  
  iVar1 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 != 2) {
    AsicNotSupportFunc(param_1,"AsicGreenAPOnOffCtrl");
    return 0;
  }
  local_12 = CONCAT11(param_3,param_2);
  uVar2 = MtCmdExtGreenAPOnOffCtrl(param_1,local_12);
  return uVar2;
}

