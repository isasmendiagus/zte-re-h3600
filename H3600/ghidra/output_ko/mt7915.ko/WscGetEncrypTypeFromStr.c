// module: mt7915.ko
// function: WscGetEncrypTypeFromStr @ 0x1e6e50
// size: 124 bytes
//

undefined4 WscGetEncrypTypeFromStr(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = rtstrcasecmp(param_1,&_LC140);
  if (iVar1 == 1) {
    return 1;
  }
  iVar1 = rtstrcasecmp(param_1,&_LC141);
  if (iVar1 != 1) {
    iVar1 = rtstrcasecmp(param_1,&_LC142);
    if (iVar1 != 1) {
      iVar1 = rtstrcasecmp(param_1,&_LC143);
      if (iVar1 == 1) {
        uVar2 = 8;
      }
      else {
        uVar2 = 0;
      }
      return uVar2;
    }
    return 4;
  }
  return 2;
}

