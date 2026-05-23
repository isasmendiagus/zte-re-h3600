// module: mt7915.ko
// function: MakeErpIE @ 0xb3684
// size: 80 bytes
//

void MakeErpIE(int param_1,int param_2,int *param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = *param_3;
  iVar3 = param_4 + iVar2;
  *(undefined1 *)(param_4 + iVar2) = 0x2a;
  *(undefined1 *)(iVar3 + 1) = 1;
  iVar1 = *(int *)(param_2 + 0x14);
  if (iVar1 == 1) {
    *(undefined *)(iVar3 + 2) = (&DAT_0036b8a1)[param_1];
    iVar1 = *(int *)(param_2 + 0x14);
  }
  if (iVar1 == 2) {
    *(undefined1 *)(iVar3 + 2) = 4;
  }
  *param_3 = iVar2 + 3;
  return;
}

