// module: mt7915.ko
// function: show_wdev_info @ 0xe194c
// size: 140 bytes
//

undefined4 show_wdev_info(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)(param_1 + 8);
  iVar2 = 0;
  while( true ) {
    piVar1 = piVar1 + 1;
    if (*piVar1 == param_2) break;
    iVar2 = iVar2 + 1;
    if (iVar2 == 0x68) {
      if (DebugLevel < 1) {
        return 0;
      }
      printk("ERR! Cannot found required wdev(%p)!\n");
      return 0;
    }
  }
  if (DebugLevel < 1) {
    return 1;
  }
  printk("WDEV Instance(%d) Info:\n",iVar2,DebugLevel,iVar2,param_4);
  return 1;
}

