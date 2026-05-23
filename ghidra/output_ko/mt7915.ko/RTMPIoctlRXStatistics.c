// module: mt7915.ko
// function: RTMPIoctlRXStatistics @ 0x3b5f8
// size: 648 bytes
//

undefined4 RTMPIoctlRXStatistics(undefined4 param_1,int param_2)

{
  char *pcVar1;
  size_t sVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int *piVar6;
  char *__s1;
  undefined4 uVar7;
  char *pcVar8;
  char *pcVar9;
  undefined1 auStack_28 [4];
  char *local_24;
  
  if (2 < DebugLevel) {
    printk("%s----------------->\n","RTMPIoctlRXStatistics");
  }
  os_alloc_mem(0,&local_24,*(ushort *)(param_2 + 0x14) + 1);
  if (local_24 == (char *)0x0) {
    return 0xfffffff4;
  }
  uVar4 = (uint)*(ushort *)(param_2 + 0x14);
  uVar5 = *(uint *)(((uint)auStack_28 & 0xffffe000) + 8);
  if (!CARRY4(*(uint *)(param_2 + 0x10),uVar4) && *(uint *)(param_2 + 0x10) + uVar4 <= uVar5) {
    uVar5 = 0;
  }
  if (uVar5 == 0) {
    iVar3 = __copy_from_user();
    if (iVar3 != 0) goto LAB_0003b790;
    uVar5 = (uint)*(ushort *)(param_2 + 0x14);
  }
  else {
    uVar5 = 0;
    if (uVar4 != 0) {
      __memzero(local_24,uVar4);
LAB_0003b790:
      os_free_mem(local_24);
      return 0xfffffff2;
    }
  }
  __s1 = local_24;
  local_24[uVar5] = '\0';
  if (DebugLevel < 3) {
    pcVar1 = strchr(local_24,0x3d);
    pcVar9 = (char *)0x0;
    if (pcVar1 == (char *)0x0) goto LAB_0003b6c4;
    sVar2 = strlen(pcVar1);
    if (sVar2 < 2) {
LAB_0003b764:
      pcVar9 = (char *)0x0;
      goto LAB_0003b6c4;
    }
LAB_0003b6ac:
    pcVar8 = pcVar1 + 1;
    *pcVar1 = '\0';
    __s1 = local_24;
    pcVar9 = pcVar8;
    if (DebugLevel < 3) goto LAB_0003b6c4;
    if (pcVar8 == (char *)0x0) goto LAB_0003b820;
  }
  else {
    printk("%s(): Before check, this_char = %s\n","RTMPIoctlRXStatistics",local_24);
    __s1 = local_24;
    pcVar1 = strchr(local_24,0x3d);
    if ((pcVar1 != (char *)0x0) && (sVar2 = strlen(pcVar1), 1 < sVar2)) goto LAB_0003b6ac;
    if (DebugLevel < 3) goto LAB_0003b764;
LAB_0003b820:
    pcVar8 = "";
    pcVar9 = (char *)0x0;
  }
  printk("%s(): After check, this_char = %s, value = %s\n","RTMPIoctlRXStatistics",__s1,pcVar8);
  __s1 = local_24;
LAB_0003b6c4:
  DAT_005f1850 = (int *)&DAT_0032db7c;
  piVar6 = DAT_005f1850;
  pcVar1 = DAT_0032db7c;
  do {
    DAT_005f1850 = piVar6;
    if (pcVar1 == (char *)0x0) {
LAB_0003b7a4:
      if (DebugLevel < 3) {
        uVar7 = 0xffffffea;
        local_24 = __s1;
      }
      else {
        printk("IOCTL::(iwpriv) Command not Support [%s = %s]\n",__s1,pcVar9);
        uVar7 = 0xffffffea;
LAB_0003b740:
        if (2 < DebugLevel) {
          printk("%s<-----------------\n","RTMPIoctlRXStatistics");
        }
      }
      os_free_mem(local_24);
      return uVar7;
    }
    iVar3 = strcmp(__s1,pcVar1);
    if (iVar3 == 0) {
      iVar3 = (*(code *)piVar6[1])(param_1,pcVar9,param_2);
      if (iVar3 == 0) {
        uVar7 = 0xffffffea;
      }
      else {
        uVar7 = 0;
      }
      __s1 = local_24;
      if (*DAT_005f1850 != 0) goto LAB_0003b740;
      goto LAB_0003b7a4;
    }
    piVar6 = piVar6 + 2;
    pcVar1 = (char *)*piVar6;
  } while( true );
}

