// module: tm.ko
// function: tm_acl_setMtchInfo @ 0x60ea0
// size: 392 bytes
//

void tm_acl_setMtchInfo(char *param_1,int param_2)

{
  uint uVar1;
  char *pcVar2;
  undefined4 uVar3;
  char *pcVar4;
  char *pcVar5;
  
  if (param_1 == (char *)0x0 || param_2 == 0) {
    printk("[%s] params is NULL\n","zte_sw_api.c");
    return;
  }
  if ((param_1[0x28] == '\x06' || param_1[0x28] == '\x11') && (is3TupleRule == 0)) {
    *(undefined4 *)(param_2 + 0x1c) = 0x301600;
  }
  else {
    uVar3 = 0x401600;
    if (*param_1 != '\0') {
      uVar3 = 0x1600;
    }
    *(undefined4 *)(param_2 + 0x1c) = uVar3;
    *(uint *)(param_2 + 8) = (uint)(byte)param_1[0x9e];
  }
  pcVar2 = param_1 + 0x13;
  pcVar5 = (char *)(param_2 + 0x6b);
  do {
    pcVar2 = pcVar2 + 1;
    pcVar4 = pcVar5 + 1;
    *pcVar4 = *pcVar2;
    pcVar5[5] = -1;
    pcVar5 = pcVar4;
  } while (pcVar4 != (char *)(param_2 + 0x6f));
  if (1 < g_tm_debug_level) {
    printk("acl filed dip:%d.%d.%d.%d\n",*(undefined1 *)(param_2 + 0x6c),
           *(undefined1 *)(param_2 + 0x6d),*(undefined1 *)(param_2 + 0x6e),
           *(undefined1 *)(param_2 + 0x6f));
  }
  uVar1 = g_tm_debug_level;
  pcVar2 = param_1 + 3;
  pcVar5 = (char *)(param_2 + 99);
  do {
    pcVar2 = pcVar2 + 1;
    pcVar4 = pcVar5 + 1;
    *pcVar4 = *pcVar2;
    pcVar5[5] = -1;
    pcVar5 = pcVar4;
  } while (pcVar4 != (char *)(param_2 + 0x67));
  if (uVar1 < 2) {
    *(char *)(param_2 + 0x62) = param_1[0x28];
    *(undefined2 *)(param_2 + 0x76) = *(undefined2 *)(param_1 + 0x26);
    *(undefined2 *)(param_2 + 0x74) = *(undefined2 *)(param_1 + 0x24);
  }
  else {
    printk("acl filed sip:%d.%d.%d.%d\n",*(undefined1 *)(param_2 + 100),
           *(undefined1 *)(param_2 + 0x65),*(undefined1 *)(param_2 + 0x66),
           *(undefined1 *)(param_2 + 0x67));
    uVar1 = g_tm_debug_level;
    *(char *)(param_2 + 0x62) = param_1[0x28];
    *(undefined2 *)(param_2 + 0x76) = *(undefined2 *)(param_1 + 0x26);
    *(undefined2 *)(param_2 + 0x74) = *(undefined2 *)(param_1 + 0x24);
    if (1 < uVar1) {
      printk("acl filed protocol %d, dport %d, sport %d\n");
      return;
    }
  }
  return;
}

