// module: mt7915.ko
// function: entrytb_traversal @ 0x14d210
// size: 112 bytes
//

int entrytb_traversal(int param_1,code *param_2,undefined4 param_3)

{
  uint uVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  
  iVar4 = 0;
  piVar2 = (int *)(param_1 + 0xa1d20);
  uVar3 = 0;
  while( true ) {
    uVar1 = HcGetMaxStaNum(param_1);
    bVar5 = uVar1 <= uVar3;
    uVar3 = uVar3 + 1;
    if ((bVar5) || ((*piVar2 == 0x20001 && (iVar4 = (*param_2)(piVar2,param_3), iVar4 == 1))))
    break;
    piVar2 = piVar2 + 0x530;
  }
  return iVar4;
}

