// module: mt7915.ko
// function: CmdIORead32 @ 0x1c4adc
// size: 100 bytes
//

void CmdIORead32(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_20;
  undefined4 local_1c;
  
  iVar1 = hc_get_mcu_ctrl();
  uVar2 = hc_get_hdev_privdata(param_1);
  if (*(int *)(iVar1 + 0x180) != 3) {
    CmdInitAccessRegRead(uVar2,param_2,param_3);
    return;
  }
  local_20 = param_2;
  MtCmdMultipleMacRegAccessRead(uVar2,&local_20,1);
  *param_3 = local_1c;
  return;
}

