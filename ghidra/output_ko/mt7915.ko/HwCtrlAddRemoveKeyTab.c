// module: mt7915.ko
// function: HwCtrlAddRemoveKeyTab @ 0xaeff8
// size: 20 bytes
//

undefined4
HwCtrlAddRemoveKeyTab(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  AsicAddRemoveKeyTab(param_1,*(undefined4 *)(param_2 + 8),param_3,param_4,param_4);
  return 0;
}

