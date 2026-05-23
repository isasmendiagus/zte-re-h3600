// module: mt7915.ko
// function: RcUpdateChannel @ 0xac6d8
// size: 20 bytes
//

undefined4 RcUpdateChannel(int param_1,undefined1 param_2,undefined1 param_3)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 4);
  *(undefined1 *)(iVar1 + 4) = param_2;
  *(undefined1 *)(iVar1 + 9) = param_3;
  return 0;
}

