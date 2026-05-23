// module: mt7915.ko
// function: mtf_set_air_monitor_enable @ 0x1973d8
// size: 1088 bytes
//

undefined4 mtf_set_air_monitor_enable(int param_1,uint param_2,uint param_3)

{
  byte bVar1;
  uint uVar2;
  char *pcVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  undefined1 *local_50;
  void *local_4c;
  undefined1 auStack_48 [4];
  char local_44;
  undefined4 local_3d;
  undefined4 local_39;
  undefined1 local_35 [10];
  undefined1 local_2b;
  undefined1 local_2a;
  undefined1 local_29;
  
  local_50 = (undefined1 *)0x0;
  local_4c = (void *)0x0;
  __memzero(local_35,0xd);
  __memzero(&local_3d,8);
  os_alloc_mem(param_1,&local_4c,0x15);
  if (local_4c == (void *)0x0) {
    return 0;
  }
  os_alloc_mem(param_1,&local_50,8);
  if (local_50 == (undefined1 *)0x0) goto LAB_001974f0;
  __memzero(local_50,8);
  if (2 < DebugLevel) {
    printk("--> %s()\n","mtf_set_air_monitor_enable");
  }
  if (param_3 == 0) {
    *local_50 = 0;
    local_50[1] = 0;
LAB_0019751c:
    MtCmdSmeshConfigSet(param_1,local_50,auStack_48);
    uVar2 = (uint)(local_44 != '\0');
  }
  else {
    if (param_3 == 1) {
      *local_50 = 1;
      local_50[1] = 0;
      goto LAB_0019751c;
    }
    uVar2 = 0;
  }
  if (uVar2 == param_2) goto LAB_00197494;
  if (param_2 == 0) {
    if (uVar2 != 1) goto LAB_00197494;
    pcVar4 = (char *)(param_1 + 0xa37674);
    pcVar3 = pcVar4;
    do {
      if ((*pcVar3 != '\0') && ((byte)pcVar3[2] == param_3)) {
        __memzero(pcVar3,4);
      }
      pcVar3 = pcVar3 + 4;
    } while (pcVar3 != (char *)(param_1 + 0xa37694));
    iVar5 = param_1 + param_3 * 4;
    pcVar3 = (char *)(param_1 + 0xa37234);
    do {
      if ((*pcVar3 != '\0') && ((byte)pcVar3[1] == param_3)) {
        local_3d = CONCAT31(local_3d._1_3_,pcVar3[2]);
        local_2a = 1;
        local_2b = 1;
        local_35[0] = 0;
        local_29 = (char)param_3;
        memmove(local_4c,local_35,0xd);
        *(undefined4 *)((int)local_4c + 0xd) = local_3d;
        *(undefined4 *)((int)local_4c + 0x11) = local_39;
        MtCmdMuarConfigSet(param_1,local_4c);
        iVar6 = *(int *)(pcVar3 + 0x40);
        if (iVar6 != 0) {
          if (param_3 == 1) {
            bVar1 = *(byte *)(iVar6 + 0x17a) & 0xfd;
          }
          else {
            bVar1 = *(byte *)(iVar6 + 0x17a) & 0xfe;
          }
          *(byte *)(iVar6 + 0x17a) = bVar1;
          if (bVar1 == 0) {
            if (0 < DebugLevel) {
              printk("%s::call MacTableDeleteEntry(WCID=%d)- %02x:%02x:%02x:%02x:%02x:%02x\n",
                     "mtf_set_air_monitor_enable",*(undefined2 *)(iVar6 + 0xe0),
                     *(undefined1 *)(iVar6 + 0xec),*(undefined1 *)(iVar6 + 0xed),
                     *(undefined1 *)(iVar6 + 0xee),*(undefined1 *)(iVar6 + 0xef),
                     *(undefined1 *)(iVar6 + 0xf0),*(undefined1 *)(iVar6 + 0xf1));
            }
            MacTableDeleteEntry(param_1,*(undefined2 *)(iVar6 + 0xe0),iVar6 + 0xec);
          }
        }
        *(int *)(iVar5 + 0xa3769c) = *(int *)(iVar5 + 0xa3769c) + -1;
        __memzero(pcVar3,0x44);
      }
      pcVar3 = pcVar3 + 0x44;
    } while (pcVar3 != pcVar4);
    if (param_3 == 0) {
      *local_50 = 0;
      local_50[1] = 1;
      local_50[2] = 0;
      MtCmdSmeshConfigSet(param_1,local_50,auStack_48);
    }
    else {
      if (param_3 != 1) goto LAB_001974dc;
      *local_50 = 1;
      local_50[1] = 1;
      local_50[2] = 0;
      MtCmdSmeshConfigSet(param_1,local_50,auStack_48);
    }
    if (*(int *)(param_1 + 0xa376a0) + *(int *)(param_1 + 0xa3769c) == 0) {
      *(undefined1 *)(param_1 + 0xa37233) = 0;
      __memzero((char *)(param_1 + 0xa37234),0x440);
      __memzero(pcVar4,0x20);
    }
  }
  else {
    if (param_3 == 0) {
      *local_50 = 0;
      local_50[1] = 1;
      local_50[2] = 1;
    }
    else {
      if (param_3 != 1) {
LAB_001974dc:
        if (0 < DebugLevel) {
          printk("%s():: wrong band index(%d)\n","mtf_set_air_monitor_enable",param_3);
        }
        os_free_mem(local_50);
LAB_001974f0:
        os_free_mem(local_4c);
        return 0;
      }
      *local_50 = 1;
      local_50[1] = 1;
      local_50[2] = 1;
    }
    apply_mntr_ruleset_smesh(param_1,local_50);
    MtCmdSmeshConfigSet(param_1,local_50,auStack_48);
    *(undefined1 *)(param_1 + 0xa37233) = 1;
  }
LAB_00197494:
  os_free_mem(local_50);
  os_free_mem(local_4c);
  if (DebugLevel < 3) {
    return 1;
  }
  printk("<-- %s()\n","mtf_set_air_monitor_enable");
  return 1;
}

