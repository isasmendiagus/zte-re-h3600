// module: mt7915.ko
// function: set_fwcmd_timeout_print_cnt @ 0xc40f0
// size: 112 bytes
//

undefined4 set_fwcmd_timeout_print_cnt(int param_1,undefined4 param_2)

{
  int iVar1;
  short sVar2;
  char *pcVar3;
  
  sVar2 = os_str_tol(param_2,0,10);
  iVar1 = DebugLevel;
  *(short *)(param_1 + 0xa7d0b8) = sVar2;
  if (0 < iVar1) {
    pcVar3 = "";
    if (sVar2 == 0) {
      pcVar3 = "(unlimited)";
    }
    printk("%s(): count = %d %s\n","set_fwcmd_timeout_print_cnt",sVar2,pcVar3);
  }
  return 1;
}

