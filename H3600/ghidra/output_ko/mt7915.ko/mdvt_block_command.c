// module: mt7915.ko
// function: mdvt_block_command @ 0x1d74e4
// size: 144 bytes
//

undefined4 mdvt_block_command(int param_1,int param_2)

{
  char *pcVar1;
  int iVar2;
  undefined1 *puVar3;
  
  if (param_1 == 0) {
    return 0;
  }
  if (*(char *)(param_1 + 0xa7c23f) == '\0') {
    return 0;
  }
  if (u4MdvtBypassCmdTableSize == 0) {
    return 1;
  }
  puVar3 = arMdvtBypassCmdTable;
  iVar2 = 0;
  while ((pcVar1 = puVar3 + 1, puVar3 = puVar3 + 2, *pcVar1 != *(char *)(param_2 + 3) ||
         (*(char *)(param_2 + 2) != arMdvtBypassCmdTable[iVar2 * 2]))) {
    iVar2 = iVar2 + 1;
    if (iVar2 == u4MdvtBypassCmdTableSize) {
      return 1;
    }
  }
  return 0;
}

