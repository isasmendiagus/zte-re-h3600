// module: mt7915.ko
// function: PMF_AddMMIE @ 0x21a95c
// size: 296 bytes
//

void PMF_AddMMIE(char *param_1,int param_2,int param_3)

{
  int iVar1;
  char cVar2;
  char *pcVar3;
  int iVar4;
  
  if (param_3 - 0x18U < 0x13) {
    if (DebugLevel < 0) {
      return;
    }
    printk("[PMF]%s : the total length(%d) is too short\n","PMF_AddMMIE",param_3 - 0x18U);
    return;
  }
  if (param_1 == (char *)0x0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("[PMF]%s : No related PMF configuation\n","PMF_AddMMIE");
    return;
  }
  if (*param_1 == '\0') {
    if (DebugLevel < 0) {
      return;
    }
    printk("[PMF]%s : PMF is disabled\n","PMF_AddMMIE");
    return;
  }
  cVar2 = param_1[0xb];
  iVar4 = param_2 + param_3 + -0x10;
  os_zero_mem(iVar4,0x10);
  iVar1 = (uint)(cVar2 == '\x05') * 6;
  *(char *)(param_2 + param_3 + -0x10) = param_1[0xb];
  os_move_mem((void *)(iVar4 + 2),param_1 + iVar1 + 0x4c,6);
  pcVar3 = param_1 + iVar1 + 0x4b;
  do {
    pcVar3 = pcVar3 + 1;
    cVar2 = *pcVar3;
    *pcVar3 = cVar2 + '\x01';
    if ((char)(cVar2 + '\x01') != '\0') break;
  } while (pcVar3 != param_1 + iVar1 + 0x51);
  *(byte *)(param_2 + 1) = *(byte *)(param_2 + 1) & 0xbf;
  return;
}

