// module: mt7915.ko
// function: Set_AssocHistory_Proc @ 0x281d8
// size: 84 bytes
//

undefined4 Set_AssocHistory_Proc(int param_1,char *param_2)

{
  int iVar1;
  
  if (param_1 == 0) {
    return 0;
  }
  iVar1 = strcmp(param_2,"0");
  if (iVar1 != 0) {
    return 0;
  }
  __memzero(param_1 + 0xa7dfb8,0x8ca4);
  return 1;
}

