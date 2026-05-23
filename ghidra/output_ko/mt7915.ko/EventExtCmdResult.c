// module: mt7915.ko
// function: EventExtCmdResult @ 0x1c3e8c
// size: 84 bytes
//

void EventExtCmdResult(undefined4 param_1,undefined1 *param_2,undefined4 param_3,undefined4 param_4)

{
  if (DebugLevel < 4) {
    return;
  }
  printk("%s: EventExtCmdResult.ucExTenCID = 0x%x\n","EventExtCmdResult",*param_2);
  if (DebugLevel < 4) {
    return;
  }
  printk("%s: EventExtCmdResult.u4Status = 0x%x\n","EventExtCmdResult",*(undefined4 *)(param_2 + 4),
         param_4);
  return;
}

