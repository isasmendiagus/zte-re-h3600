// module: mt7915.ko
// function: RcUpdateRadio @ 0xac6ec
// size: 44 bytes
//

undefined4
RcUpdateRadio(int param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
             undefined1 param_5,undefined1 param_6)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 4);
  *(undefined1 *)(iVar1 + 6) = param_3;
  *(undefined1 *)(iVar1 + 7) = param_2;
  *(undefined1 *)(iVar1 + 5) = param_4;
  *(undefined1 *)(iVar1 + 8) = param_5;
  *(undefined1 *)(iVar1 + 0xd) = param_6;
  return 0;
}

