// module: mt7915.ko
// function: HwCtrlRemoveReptEntry @ 0xaf0d8
// size: 24 bytes
//

undefined4
HwCtrlRemoveReptEntry(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  RTMPRemoveRepeaterEntry
            (param_1,**(undefined1 **)(param_2 + 8),param_3,*(undefined1 **)(param_2 + 8),param_4);
  return 0;
}

