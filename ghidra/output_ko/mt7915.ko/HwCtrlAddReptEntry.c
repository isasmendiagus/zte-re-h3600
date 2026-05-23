// module: mt7915.ko
// function: HwCtrlAddReptEntry @ 0xaf0f0
// size: 24 bytes
//

undefined4 HwCtrlAddReptEntry(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  RTMPInsertRepeaterEntry
            (param_1,**(undefined4 **)(param_2 + 8),*(undefined4 **)(param_2 + 8) + 1,param_4,
             param_4);
  return 0;
}

