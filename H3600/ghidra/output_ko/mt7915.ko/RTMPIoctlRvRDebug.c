// module: mt7915.ko
// function: RTMPIoctlRvRDebug @ 0x155808
// size: 476 bytes
//

undefined4 RTMPIoctlRvRDebug(undefined4 param_1,int param_2)

{
  char *pcVar1;
  size_t sVar2;
  int iVar3;
  int *piVar4;
  undefined4 uVar5;
  char *__s;
  char *pcVar6;
  
  if (DebugLevel < 3) {
    __s = *(char **)(param_2 + 0x10);
    pcVar1 = strchr(__s,0x3d);
    pcVar6 = (char *)0x0;
    if (pcVar1 == (char *)0x0) goto LAB_00155868;
LAB_00155840:
    sVar2 = strlen(pcVar1);
    *pcVar1 = '\0';
    if (sVar2 < 2) goto LAB_00155964;
    pcVar1 = pcVar1 + 1;
    pcVar6 = pcVar1;
    if (DebugLevel < 3) goto LAB_00155868;
    if (pcVar1 == (char *)0x0) goto LAB_00155998;
  }
  else {
    printk("%s----------------->\n","RTMPIoctlRvRDebug");
    __s = *(char **)(param_2 + 0x10);
    if (DebugLevel < 3) {
      pcVar1 = strchr(__s,0x3d);
      if (pcVar1 == (char *)0x0) {
        pcVar6 = (char *)0x0;
        goto LAB_00155868;
      }
      goto LAB_00155840;
    }
    printk("%s(): Before check, this_char = %s\n","RTMPIoctlRvRDebug",__s);
    pcVar1 = strchr(__s,0x3d);
    if (pcVar1 != (char *)0x0) goto LAB_00155840;
LAB_00155964:
    if (DebugLevel < 3) {
      pcVar6 = (char *)0x0;
      goto LAB_00155868;
    }
LAB_00155998:
    pcVar1 = "";
    pcVar6 = (char *)0x0;
  }
  printk("%s(): After check, this_char = %s, value = %s\n","RTMPIoctlRvRDebug",__s,pcVar1);
LAB_00155868:
  DAT_005f3d30 = (int *)&DAT_0034d4a8;
  piVar4 = DAT_005f3d30;
  pcVar1 = DAT_0034d4a8;
  do {
    DAT_005f3d30 = piVar4;
    if (pcVar1 == (char *)0x0) {
      uVar5 = 0;
LAB_001558fc:
      if (2 < DebugLevel) {
        printk("PRTMP_PRIVATE_RD_PROC->name == NULL");
      }
      rd_dashboard(param_1,param_2);
      return uVar5;
    }
    iVar3 = strcmp(__s,pcVar1);
    if (iVar3 == 0) {
      iVar3 = (*(code *)piVar4[1])(param_1,pcVar6,param_2);
      if (iVar3 == 0) {
        uVar5 = 0xffffffea;
      }
      else {
        uVar5 = 0;
      }
      if (*DAT_005f3d30 != 0) {
        if (2 < DebugLevel) {
          printk("%s<-----------------\n","RTMPIoctlRvRDebug");
        }
        return uVar5;
      }
      goto LAB_001558fc;
    }
    piVar4 = piVar4 + 2;
    pcVar1 = (char *)*piVar4;
  } while( true );
}

