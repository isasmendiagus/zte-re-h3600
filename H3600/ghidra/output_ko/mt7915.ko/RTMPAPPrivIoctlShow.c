// module: mt7915.ko
// function: RTMPAPPrivIoctlShow @ 0x35c24
// size: 608 bytes
//

undefined4 RTMPAPPrivIoctlShow(undefined4 param_1,int param_2)

{
  char *__s;
  char *pcVar1;
  size_t sVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  undefined4 uVar7;
  char *local_30;
  char *local_2c [2];
  
  local_2c[0] = (char *)0x0;
  local_30 = (char *)0x0;
  os_alloc_mem(0,local_2c,*(ushort *)(param_2 + 0x14) + 1);
  if (local_2c[0] == (char *)0x0) {
    return 0xfffffff4;
  }
  uVar4 = (uint)*(ushort *)(param_2 + 0x14);
  uVar5 = *(uint *)(((uint)&local_30 & 0xffffe000) + 8);
  if (!CARRY4(*(uint *)(param_2 + 0x10),uVar4) && *(uint *)(param_2 + 0x10) + uVar4 <= uVar5) {
    uVar5 = 0;
  }
  if (uVar5 == 0) {
    iVar3 = __copy_from_user();
    if (iVar3 != 0) goto LAB_00035ddc;
    uVar5 = (uint)*(ushort *)(param_2 + 0x14);
  }
  else {
    uVar5 = 0;
    if (uVar4 != 0) {
      __memzero(local_2c[0],uVar4);
LAB_00035ddc:
      os_free_mem(local_2c[0]);
      return 0xfffffff2;
    }
  }
  uVar7 = 0;
  local_2c[0][uVar5] = '\0';
  local_30 = local_2c[0];
  do {
    do {
      __s = strsep(&local_30,",");
      if (__s == (char *)0x0) goto LAB_00035da0;
    } while (*__s == '\0');
    if (DebugLevel < 3) {
      pcVar1 = strchr(__s,0x3d);
      if ((pcVar1 == (char *)0x0) || (sVar2 = strlen(pcVar1), sVar2 < 2)) {
LAB_00035db4:
        pcVar1 = (char *)0x0;
      }
      else {
LAB_00035d04:
        pcVar6 = pcVar1 + 1;
        *pcVar1 = '\0';
        pcVar1 = pcVar6;
        if (2 < DebugLevel) {
          if (pcVar6 == (char *)0x0) goto LAB_00035e34;
          goto LAB_00035e40;
        }
      }
    }
    else {
      printk("%s(): Before check, this_char=%s\n","RTMPAPPrivIoctlShow",__s);
      pcVar1 = strchr(__s,0x3d);
      if ((pcVar1 != (char *)0x0) && (sVar2 = strlen(pcVar1), 1 < sVar2)) goto LAB_00035d04;
      if (DebugLevel < 3) goto LAB_00035db4;
LAB_00035e34:
      pcVar6 = "";
      pcVar1 = (char *)0x0;
LAB_00035e40:
      printk("%s(): after check, this_char=%s, value=%s\n","RTMPAPPrivIoctlShow",__s,pcVar6);
    }
    DAT_005f184c = &DAT_0032d4bc;
    iVar3 = DAT_0032d4bc;
    while( true ) {
      if (iVar3 == 0) goto LAB_00035d90;
      iVar3 = rtstrcasecmp(__s);
      if (iVar3 == 1) break;
      iVar3 = DAT_005f184c[2];
      DAT_005f184c = DAT_005f184c + 2;
    }
    iVar3 = (*(code *)DAT_005f184c[1])(param_1,pcVar1);
    if (iVar3 == 0) {
      uVar7 = 0xffffffea;
    }
  } while (*DAT_005f184c != 0);
LAB_00035d90:
  if (DebugLevel < 3) {
    uVar7 = 0xffffffea;
  }
  else {
    printk("IOCTL::(iwpriv) Command not Support [%s=%s]\n",__s,pcVar1);
    uVar7 = 0xffffffea;
  }
LAB_00035da0:
  os_free_mem(local_2c[0]);
  return uVar7;
}

