// module: mt7915.ko
// function: CmdExtWtblUpdateCb @ 0x1c41cc
// size: 188 bytes
//

void CmdExtWtblUpdateCb(int param_1,undefined1 *param_2,int param_3)

{
  void *__dest;
  
  __dest = *(void **)(param_1 + 0xc);
  if (__dest != (void *)0x0) {
    if (3 < DebugLevel) {
      printk("%s: Copy query result to buffer\n","CmdExtWtblUpdateCb");
    }
    os_move_mem(__dest,param_2 + 0x1c,param_3 - 0x1c);
    return;
  }
  if (3 < DebugLevel) {
    printk("%s: EventExtCmdResult.ucExTenCID = 0x%x\n","CmdExtWtblUpdateCb",*param_2);
    if (3 < DebugLevel) {
      printk("%s: EventExtCmdResult.u4Status = 0x%x\n","CmdExtWtblUpdateCb",
             *(undefined4 *)(param_2 + 4));
      return;
    }
  }
  return;
}

