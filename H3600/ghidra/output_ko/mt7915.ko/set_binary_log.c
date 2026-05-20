// module: mt7915.ko
// function: set_binary_log @ 0x1d4ae4
// size: 204 bytes
//

undefined4 set_binary_log(int param_1,char *param_2)

{
  int iVar1;
  undefined1 uVar2;
  char *pcVar3;
  int iVar4;
  char *local_14 [2];
  
  if ((param_2 != (char *)0x0) && (*param_2 != '\0')) {
    local_14[0] = param_2;
    pcVar3 = strsep(local_14,":");
    iVar4 = os_str_toul(pcVar3,0,10);
    if ((local_14[0] == (char *)0x0) || (*local_14[0] == '\0')) {
      uVar2 = 0xff;
    }
    else {
      uVar2 = os_str_toul(local_14[0],0,10);
    }
    iVar1 = DebugLevel;
    if (iVar4 == 0) {
      *(undefined1 *)(param_1 + 0xa7cc53) = uVar2;
      if (0 < iVar1) {
        printk("%s: set debug_level_ctrl[%d] = 0x%x\n","set_binary_log",0);
        return 1;
      }
      return 1;
    }
  }
  return 0;
}

