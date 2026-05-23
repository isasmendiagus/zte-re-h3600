// module: mt7915.ko
// function: a4_apcli_peer_enable @ 0x9fd5c
// size: 336 bytes
//

undefined4 a4_apcli_peer_enable(undefined4 param_1,int param_2,int *param_3,uint param_4)

{
  int iVar1;
  uint uVar2;
  undefined2 local_20;
  undefined2 local_1e;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  
  if (param_3 == (int *)0x0 || param_2 == 0) {
    return 0;
  }
  if ((*param_3 == 2) &&
     ((*(int *)(param_2 + 0x12e4) == 0 || (*(char *)(param_2 + 0x3cc8) != '\x01')))) {
    uVar2 = (uint)*(byte *)(param_3 + 0x3a);
    if (uVar2 == 0) {
      os_zero_mem(&local_20,8);
      if (1 < DebugLevel) {
        printk("a4_apcli_peer_enable enabled A4 for entry : %02x:%02x:%02x:%02x:%02x:%02x\n",
               (char)param_3[0x3b],*(undefined1 *)((int)param_3 + 0xed),
               *(undefined1 *)((int)param_3 + 0xee),*(undefined1 *)((int)param_3 + 0xef),
               (char)param_3[0x3c],*(undefined1 *)((int)param_3 + 0xf1));
      }
      local_1e = 8;
      local_20 = 6;
      local_1c = 1;
      local_1b = 1;
      local_1a = 0;
      iVar1 = CmdExtWtblUpdate(param_1,(short)param_3[0x38],2,&local_20,8);
      if (iVar1 != 0) {
        return 0;
      }
      if (0 < DebugLevel) {
        printk("SET_A4_ENTRY OK!\n");
      }
      uVar2 = (uint)*(byte *)(param_3 + 0x3a);
    }
    if (uVar2 < param_4) {
      *(char *)(param_2 + 0x213392) = (char)param_4;
      *(char *)(param_3 + 0x3a) = (char)param_4;
    }
    return 1;
  }
  return 0;
}

