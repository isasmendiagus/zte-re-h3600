// module: mt7915.ko
// function: CmdIOWrite32 @ 0x1c4a7c
// size: 96 bytes
//

void CmdIOWrite32(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_20;
  undefined4 local_1c;
  
  iVar1 = hc_get_mcu_ctrl();
  uVar2 = hc_get_hdev_privdata(param_1);
  if (*(int *)(iVar1 + 0x180) != 3) {
    CmdInitAccessRegWrite(uVar2,param_2,param_3);
    return;
  }
  local_20 = param_2;
  local_1c = param_3;
  MtCmdMultipleMacRegAccessWrite(uVar2,&local_20,1);
  return;
}

