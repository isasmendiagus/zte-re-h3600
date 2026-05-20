// module: mt7915.ko
// function: RcGetBandIdxByRf @ 0xac874
// size: 24 bytes
//

undefined1 RcGetBandIdxByRf(void)

{
  undefined1 uVar1;
  int iVar2;
  
  iVar2 = FUN_000ab5f4();
  uVar1 = 0;
  if (iVar2 != 0) {
    uVar1 = **(undefined1 **)(iVar2 + 4);
  }
  return uVar1;
}

