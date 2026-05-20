// module: mt7915.ko
// function: printView @ 0x153ef0
// size: 252 bytes
//

void printView(int param_1,char *param_2)

{
  size_t sVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  char *pcVar5;
  
  sVar1 = strlen(param_2);
  sprintf(param_2 + sVar1,"%-4s | %-6s | %-15s | %s\n",&_LC38,&_LC39,&_LC40,"Status");
  _LANCHOR1 = &_LANCHOR2;
  if (_LANCHOR2 != 0) {
    iVar2 = _LANCHOR2;
    iVar3 = 0;
    do {
      puVar4 = _LANCHOR1;
      sVar1 = strlen(param_2);
      pcVar5 = "Enable";
      if (((uint)*(byte *)(param_1 + 0xa7c2e8) & puVar4[2]) == 0) {
        pcVar5 = "Disable";
      }
      sprintf(param_2 + sVar1,"%-4d | %-6s | %-15s | %s\n",iVar3,iVar2,puVar4[1],pcVar5);
      puVar4 = _LANCHOR1 + 3;
      iVar2 = _LANCHOR1[3];
      iVar3 = iVar3 + 1;
      _LANCHOR1 = puVar4;
    } while (iVar2 != 0);
  }
  return;
}

