// module: mt7915.ko
// function: StaRecUpdateTxProc @ 0x1c21dc
// size: 300 bytes
//

undefined4 StaRecUpdateTxProc(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  undefined4 local_18;
  uint local_14;
  
  piVar2 = *(int **)(param_3 + 0x9c);
  local_18 = 0;
  local_14 = 0;
  iVar3 = *(int *)(param_1 + (uint)*(ushort *)(param_3 + 2) * 0x620 + 0x2f6a4);
  os_zero_mem(&local_18,8);
  local_18 = 0x80008;
  if ((((piVar2 == (int *)0x0) || (piVar2[2] == 0)) || (*(char *)(piVar2[2] + 0x8f8) == '\0')) &&
     ((iVar3 == 0 || (*(char *)(iVar3 + 0x8f8) == '\0')))) {
    local_14 = 1;
  }
  else {
    local_14 = 0;
  }
  if ((piVar2 != (int *)0x0) && (*piVar2 == 2 || *piVar2 == 0x40001)) {
    uVar1 = local_14 | 8;
    if ((char)piVar2[0x4ef] == '\x01') {
      uVar1 = local_14 | 0x18;
    }
    local_14 = uVar1;
    if (*(char *)((int)piVar2 + 0x13bd) == '\x01') {
      local_14 = local_14 | 0x20;
    }
    if (*(char *)((int)piVar2 + 0x13be) == '\x01') {
      local_14 = local_14 | 0x40;
    }
    if (*(char *)((int)piVar2 + 0x13bf) == '\x01') {
      local_14 = local_14 | 0x80;
    }
  }
  AndesAppendCmdMsg(param_2,&local_18,8);
  return 0;
}

