// module: mt7915.ko
// function: token_rx_dmad_init @ 0x1d3a4c
// size: 96 bytes
//

int token_rx_dmad_init(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                      undefined4 param_5)

{
  int iVar1;
  bool bVar2;
  int *piVar3;
  int iVar4;
  
  iVar4 = param_1[1];
  iVar1 = iVar4 * 0x20;
  *(undefined4 *)(*param_1 + iVar4 * 0x20) = param_2;
  *(undefined4 *)(*param_1 + iVar1 + 4) = param_3;
  *(undefined4 *)(*param_1 + iVar1 + 8) = param_4;
  piVar3 = param_1 + 1;
  *(undefined4 *)(*param_1 + iVar1 + 0xc) = param_5;
  HintPreloadDataForWrite(piVar3);
  do {
    bVar2 = (bool)hasExclusiveAccess(piVar3);
  } while (!bVar2);
  *piVar3 = *piVar3 + 1;
  return iVar4;
}

