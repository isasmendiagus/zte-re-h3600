// module: mt7915.ko
// function: CmdExtStaRecUpdateRsp @ 0x1c3f90
// size: 224 bytes
//

void CmdExtStaRecUpdateRsp(int param_1,undefined1 *param_2)

{
  int iVar1;
  
  iVar1 = DebugLevel;
  if (DebugLevel < 4) {
    *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_2 + 4);
    if (*(int *)(param_2 + 4) == 0) {
      return;
    }
  }
  else {
    printk("%s::EventExtCmdResult.ucExTenCID = 0x%x\n","CmdExtStaRecUpdateRsp",*param_2);
    iVar1 = DebugLevel;
    *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_2 + 4);
    if (*(int *)(param_2 + 4) == 0) {
      if (iVar1 < 4) {
        return;
      }
      printk("%s::EventExtCmdResult.u4Status = 0x%x\n","CmdExtStaRecUpdateRsp");
      if (DebugLevel < 4) {
        return;
      }
      printk("%s::ucBssInfoIdx(%d), WlanIdx(%d), u2TotalElementNum(%d)\n","CmdExtStaRecUpdateRsp",
             param_2[8],CONCAT11(param_2[0xd],param_2[9]) & 0x3ff,*(undefined2 *)(param_2 + 10));
      return;
    }
  }
  if (iVar1 < 0) {
    return;
  }
  printk("%s::ERROR::EventExtCmdResult.u4Status = 0x%x\n","CmdExtStaRecUpdateRsp");
  return;
}

