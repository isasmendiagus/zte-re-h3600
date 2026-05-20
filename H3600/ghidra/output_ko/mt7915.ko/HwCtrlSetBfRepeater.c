// module: mt7915.ko
// function: HwCtrlSetBfRepeater @ 0xaf774
// size: 32 bytes
//

undefined4 HwCtrlSetBfRepeater(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = *(int *)(param_2 + 8);
  AsicTxBfReptClonedStaToNormalSta
            (param_1,*(undefined1 *)(iVar1 + 0xe0),*(undefined1 *)(*(int *)(iVar1 + 0xafc) + 2),
             iVar1,param_4);
  return 0;
}

