// module: mt7915.ko
// function: HwCtrlSetTxBurst @ 0xaead0
// size: 36 bytes
//

undefined4 HwCtrlSetTxBurst(undefined4 param_1,int param_2)

{
  if (*(int *)(param_2 + 8) != 0) {
    FUN_000ae92c();
    return 0;
  }
  return 1;
}

