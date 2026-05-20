// module: mt7915.ko
// function: RT_CfgSetFixedTxPhyMode @ 0xb8a30
// size: 152 bytes
//

uint RT_CfgSetFixedTxPhyMode(undefined4 param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = rtstrcasecmp(param_1,&_LC7);
  if (iVar1 == 1) {
    return 2;
  }
  iVar1 = rtstrcasecmp(param_1,&_LC6);
  if (iVar1 == 1) {
    return 1;
  }
  iVar1 = rtstrcasecmp(param_1,&_LC90);
  if (iVar1 == 1) {
    return 0;
  }
  iVar1 = rtstrcasecmp(param_1,&_LC10);
  if (iVar1 == 1) {
    return 3;
  }
  uVar2 = os_str_tol(param_1,0,10);
  if (3 < uVar2) {
    uVar2 = 0;
  }
  return uVar2;
}

