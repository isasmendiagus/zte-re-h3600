// module: mt7915.ko
// function: HwCtrlSetBaRec @ 0xaf6a0
// size: 120 bytes
//

undefined4 HwCtrlSetBaRec(undefined4 param_1,int param_2)

{
  undefined2 *puVar1;
  
  puVar1 = *(undefined2 **)(param_2 + 8);
  if (2 < DebugLevel) {
    printk("%s::CmdThread\n","HwCtrlSetBaRec");
  }
  AsicUpdateBASession(param_1,*puVar1,*(undefined1 *)(puVar1 + 1),puVar1[9],puVar1[2],
                      *(undefined1 *)(puVar1 + 3),*(undefined4 *)(puVar1 + 4),
                      *(undefined1 *)(puVar1 + 10));
  return 0;
}

