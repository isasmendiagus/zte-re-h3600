// module: mt7915.ko
// function: Send2040CoexistAction @ 0xa38fc
// size: 736 bytes
//

void Send2040CoexistAction(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined1 local_45;
  int local_44;
  int local_40;
  undefined1 auStack_3a [24];
  undefined1 local_22;
  undefined1 local_21;
  
  local_44 = 0;
  iVar3 = *(int *)(param_1 + param_2 * 0x14c0 + 0xa1d28);
  local_45 = 1;
  iVar1 = GetStaCfgByWdev(param_1,iVar3);
  iVar2 = os_alloc_mem(param_1,&local_44,0x900);
  if (iVar2 != 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("ACT - Send2040CoexistAction() allocate memory failed\n");
    return;
  }
  if (iVar1 != 0) {
    ActHeaderInit(param_1,auStack_3a,param_1 + param_2 * 0x14c0 + 0xa1e0c,iVar3 + 0x1b,
                  iVar1 + 0x212428);
  }
  iVar1 = param_1 + param_2 * 0x14c0;
  if ((*(int *)(iVar1 + 0xa1d20) == 2) &&
     (iVar2 = param_1 + param_2 * 0x14c0 + 0xa1e0c,
     ActHeaderInit(param_1,auStack_3a,iVar2,
                   &DAT_0036db73 + param_1 + (uint)*(byte *)(iVar1 + 0xa1e04) * 0x2137b0,iVar2),
     0 < DebugLevel)) {
    printk(&_LC56,*(undefined1 *)(iVar1 + 0xa1e0c),*(undefined1 *)(iVar1 + 0xa1e0d),
           *(undefined1 *)(iVar1 + 0xa1e0e),*(undefined1 *)(iVar1 + 0xa1e0f),
           *(undefined1 *)(iVar1 + 0xa1e10),*(undefined1 *)(iVar1 + 0xa1e11));
  }
  iVar1 = 0;
  local_21 = 0;
  local_22 = 4;
  MakeOutgoingFrame(local_44,&local_40,0x1a,auStack_3a,1,&BssCoexistIe,1,&local_45,1,
                    param_1 + 0x7956b5,0xffffffff);
  if (param_3 == 1) {
    iVar1 = BuildIntolerantChannelRep(param_1,local_44 + local_40);
    if (2 < DebugLevel) goto LAB_000a3bbc;
LAB_000a3ba0:
    if (iVar1 == 0) goto LAB_000a3a4c;
  }
  else {
    if (2 < DebugLevel) {
LAB_000a3bbc:
      printk("IntolerantChaRepLen=%d, BSSCoexist2040=0x%x!\n",iVar1,
             *(undefined1 *)(param_1 + 0x7956b5));
      goto LAB_000a3ba0;
    }
LAB_000a3a4c:
    if (*(char *)(param_1 + 0x7956b5) == '\0') goto LAB_000a3a7c;
    iVar1 = 0;
  }
  MiniportMMRequest(param_1,1,local_44,iVar1 + local_40);
LAB_000a3a7c:
  os_free_mem(local_44);
  if (2 < DebugLevel) {
    printk("ACT - Send2040CoexistAction( BSSCoexist2040 = 0x%x )\n",
           *(undefined1 *)(param_1 + 0x7956b5));
  }
  return;
}

