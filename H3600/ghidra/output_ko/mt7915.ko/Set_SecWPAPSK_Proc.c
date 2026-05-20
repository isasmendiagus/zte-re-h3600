// module: mt7915.ko
// function: Set_SecWPAPSK_Proc @ 0x11312c
// size: 632 bytes
//

undefined4 Set_SecWPAPSK_Proc(int *param_1,char *param_2)

{
  size_t sVar1;
  size_t sVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  char *__s;
  
  iVar7 = *param_1;
  iVar6 = *(int *)(iVar7 + 0x40);
  iVar4 = *(int *)(iVar7 + 0x3c);
  if (iVar6 == 0) {
    if (0 < DebugLevel) {
      printk("%s:: pSecConfig == NULL, arg=%s\n","Set_SecWPAPSK_Proc",param_2);
      return 0;
    }
    return 0;
  }
  sVar1 = strlen(param_2);
  if (sVar1 < 0x41) {
    __s = (char *)(iVar6 + 0x14d);
    sVar2 = strlen(__s);
    if ((sVar1 != sVar2) || (iVar5 = memcmp(param_2,__s,sVar1), iVar5 != 0)) {
      pbVar3 = (byte *)(param_1 + 0xda1ff);
      iVar5 = 0;
      do {
        if (((pbVar3[0x5c] == 1) && ((uint)*pbVar3 == param_1[iVar4 * 0x160d + 0xaecaa])) &&
           (pbVar3[0x5c] = 0, 0 < DebugLevel)) {
          printk("%s():Modify PSK and clear PMKID (idx %d)from (mbssidx %d)\n","Set_SecWPAPSK_Proc",
                 iVar5);
        }
        iVar5 = iVar5 + 1;
        pbVar3 = pbVar3 + 0x60;
      } while (iVar5 != 0x80);
      sVar1 = strlen(param_2);
    }
    os_move_mem(__s,param_2,sVar1);
    sVar1 = strlen(param_2);
    *(undefined1 *)(iVar6 + sVar1 + 0x14d) = 0;
  }
  else {
    *(undefined1 *)(iVar6 + 0x14d) = 0;
  }
  if (2 < DebugLevel) {
    printk("%s: PSK = %s\n","Set_SecWPAPSK_Proc",param_2);
  }
  if (*(char *)((int)param_1 + 0x286285) == '\x01') {
    if ((*(int *)(iVar7 + 0x38) - 0x100U & 0xfffffeff) == 0) {
      iVar4 = (uint)*(byte *)(iVar7 + 0x3c) * 0x160d + 0xae14b;
    }
    else {
      if (*(int *)(iVar7 + 0x38) != 0x400) {
        return 1;
      }
      iVar4 = (uint)*(byte *)(iVar7 + 0x3c) * 0x84dec + 0xdbb8f;
    }
    param_1 = param_1 + iVar4;
    if (param_1 != (int *)0x0) {
      __memzero((void *)((int)param_1 + 0x299d),0x40);
      param_1[0xa78] = 0;
      sVar1 = strlen(param_2);
      param_1[0xa78] = sVar1;
      memmove((void *)((int)param_1 + 0x299d),param_2,sVar1);
      return 1;
    }
  }
  return 1;
}

