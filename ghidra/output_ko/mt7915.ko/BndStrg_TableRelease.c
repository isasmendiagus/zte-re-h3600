// module: mt7915.ko
// function: BndStrg_TableRelease @ 0x9c63c
// size: 28 bytes
//

undefined4 BndStrg_TableRelease(int param_1)

{
  undefined4 uVar1;
  
  if (*(char *)(param_1 + 4) == '\0') {
    uVar1 = 5;
  }
  else {
    uVar1 = 0;
    *(undefined1 *)(param_1 + 4) = 0;
  }
  return uVar1;
}

