// module: mt7915.ko
// function: set_cp_support_en @ 0xed9ac
// size: 252 bytes
//

undefined1 set_cp_support_en(int param_1,char *param_2)

{
  undefined1 uVar1;
  int iVar2;
  int local_14 [2];
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  iVar2 = sscanf(param_2,"%u",local_14);
  if ((iVar2 == 0) || (2 < local_14[0] - 1U)) {
    if (-1 < DebugLevel) {
      printk("The Mode is invaild. Mode should be 1~3.\n");
    }
    uVar1 = 0;
  }
  else {
    *(char *)(param_1 + 0xa7beca) = (char)local_14[0];
    if (*(char *)(param_1 + 0xa7becb) == '\x01') {
      MtCmdSetCPSEnable(param_1,2);
      if (-1 < DebugLevel) {
        printk("%s: set CR4 CP_SUPPORT to Mode %d.\n","set_cp_support_en",local_14[0]);
        return 1;
      }
    }
    else if (-1 < DebugLevel) {
      printk("%s: set Driver CP_SUPPORT to Mode %d.\n","set_cp_support_en");
    }
    uVar1 = 1;
  }
  return uVar1;
}

