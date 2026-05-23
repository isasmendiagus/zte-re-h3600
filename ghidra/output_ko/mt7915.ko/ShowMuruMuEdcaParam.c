// module: mt7915.ko
// function: ShowMuruMuEdcaParam @ 0x23b37c
// size: 56 bytes
//

undefined4 ShowMuruMuEdcaParam(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = os_str_tol(param_2,0,10);
  *(bool *)(param_1 + 0x795a80) = 0 < iVar1;
  return 1;
}

