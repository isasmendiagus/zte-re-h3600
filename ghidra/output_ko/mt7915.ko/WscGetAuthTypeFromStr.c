// module: mt7915.ko
// function: WscGetAuthTypeFromStr @ 0x1e6dd4
// size: 124 bytes
//

undefined4 WscGetAuthTypeFromStr(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = rtstrcasecmp(param_1,&_LC110);
  if (iVar1 == 1) {
    return 1;
  }
  iVar1 = rtstrcasecmp(param_1,"SHARED");
  if (iVar1 != 1) {
    iVar1 = rtstrcasecmp(param_1,"WPAPSK");
    if (iVar1 != 1) {
      iVar1 = rtstrcasecmp(param_1,"WPA2PSK");
      if (iVar1 == 1) {
        uVar2 = 0x20;
      }
      else {
        uVar2 = 0;
      }
      return uVar2;
    }
    return 2;
  }
  return 4;
}

