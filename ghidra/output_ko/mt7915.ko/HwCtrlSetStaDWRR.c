// module: mt7915.ko
// function: HwCtrlSetStaDWRR @ 0xaf378
// size: 88 bytes
//

undefined4 HwCtrlSetStaDWRR(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined2 *puVar1;
  
  puVar1 = *(undefined2 **)(param_2 + 8);
  if (3 < DebugLevel) {
    printk("%s: group %d, staid %d\n","HwCtrlSetStaDWRR",*(undefined1 *)(puVar1 + 1),*puVar1,param_4
          );
  }
  vow_set_client(param_1,*(undefined1 *)(puVar1 + 1),*puVar1,*(undefined1 *)((int)puVar1 + 3));
  return 0;
}

