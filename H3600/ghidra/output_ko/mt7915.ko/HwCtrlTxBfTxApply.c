// module: mt7915.ko
// function: HwCtrlTxBfTxApply @ 0xaf738
// size: 24 bytes
//

undefined4 HwCtrlTxBfTxApply(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  BfSwitch(param_1,**(undefined1 **)(param_2 + 8),param_3,*(undefined1 **)(param_2 + 8),param_4);
  return 0;
}

