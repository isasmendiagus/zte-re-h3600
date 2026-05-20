// module: mt7915.ko
// function: CmdPatchSemRsp @ 0x1ab8dc
// size: 52 bytes
//

void CmdPatchSemRsp(int param_1,char *param_2)

{
  int iVar1;
  
  iVar1 = DebugLevel;
  *(int *)(*(int *)(param_1 + 0x1c) + 0xa78618) = (int)*param_2;
  if (iVar1 < 1) {
    return;
  }
  printk("Patch SEM Status = %d\n");
  return;
}

