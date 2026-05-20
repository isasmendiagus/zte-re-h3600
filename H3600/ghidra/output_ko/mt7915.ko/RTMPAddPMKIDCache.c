// module: mt7915.ko
// function: RTMPAddPMKIDCache @ 0x1991c
// size: 408 bytes
//

int RTMPAddPMKIDCache(int param_1,undefined4 param_2,undefined4 *param_3,void *param_4,void *param_5
                     ,byte param_6)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  iVar1 = RTMPSearchPMKIDCache();
  if (iVar1 == -1) {
    iVar2 = 0;
    uVar5 = 0;
    iVar1 = 0;
    iVar3 = param_1;
    do {
      if (*(char *)(iVar3 + 0x5c) == '\0') goto LAB_0001995c;
      if (uVar5 == 0) {
        uVar4 = *(uint *)(iVar3 + 0x58);
LAB_000199e8:
        iVar2 = iVar1;
        uVar5 = uVar4;
      }
      else {
        uVar4 = *(uint *)(iVar3 + 0x58);
        if (uVar4 < uVar5) goto LAB_000199e8;
      }
      iVar1 = iVar1 + 1;
      iVar3 = iVar3 + 0x60;
    } while (iVar1 != 0x80);
    iVar1 = iVar2;
    if (1 < DebugLevel) {
      printk("%s():Cache full, replace oldest(%d)\n","RTMPAddPMKIDCache");
    }
  }
  else if (2 < DebugLevel) {
    printk("%s(): cache found and renew it(%d)\n","RTMPAddPMKIDCache",iVar1);
  }
LAB_0001995c:
  iVar2 = iVar1 * 0x60;
  iVar3 = param_1 + iVar2;
  *(undefined1 *)(iVar3 + 0x5c) = 1;
  *(char *)(param_1 + iVar2) = (char)param_2;
  *(undefined4 *)(iVar3 + 0x58) = jiffies;
  *(undefined4 *)(iVar3 + 1) = *param_3;
  *(undefined2 *)(iVar3 + 5) = *(undefined2 *)(param_3 + 1);
  memmove((void *)(iVar3 + 7),param_4,0x10);
  memmove((void *)(param_1 + iVar2 + 0x17),param_5,(uint)param_6);
  if (2 < DebugLevel) {
    printk("%s(): add %02x:%02x:%02x:%02x:%02x:%02x cache(%d) for ra%d\n","RTMPAddPMKIDCache",
           *(undefined1 *)param_3,*(undefined1 *)((int)param_3 + 1),
           *(undefined1 *)((int)param_3 + 2),*(undefined1 *)((int)param_3 + 3),
           *(undefined1 *)(param_3 + 1),*(undefined1 *)((int)param_3 + 5),iVar1,param_2);
  }
  return iVar1;
}

