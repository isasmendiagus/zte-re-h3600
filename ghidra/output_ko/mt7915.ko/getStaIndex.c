// module: mt7915.ko
// function: getStaIndex @ 0x68658
// size: 24 bytes
//

undefined1 getStaIndex(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  
  iVar2 = ApcliCardIndex2WlanIdmMap(param_2);
  uVar1 = 0;
  if (iVar2 != 0) {
    uVar1 = *(undefined1 *)(iVar2 + 0x21);
  }
  return uVar1;
}

