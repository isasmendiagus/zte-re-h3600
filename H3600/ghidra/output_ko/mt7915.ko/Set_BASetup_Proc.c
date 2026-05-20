// module: mt7915.ko
// function: Set_BASetup_Proc @ 0xdd4b8
// size: 476 bytes
//

undefined4 Set_BASetup_Proc(int param_1,char *param_2)

{
  byte bVar1;
  size_t sVar2;
  char *__s;
  byte *__s_00;
  undefined1 *puVar3;
  int iVar4;
  undefined2 local_20;
  undefined1 local_1e [4];
  undefined1 local_1a;
  undefined1 local_19;
  
  local_20 = 0x3a;
  sVar2 = strlen(param_2);
  if ((((sVar2 < 0x13) || (__s = strchr(param_2,0x2d), __s == (char *)0x0)) ||
      (sVar2 = strlen(__s), sVar2 < 2)) || (bVar1 = os_str_tol(__s + 1,0,10), 7 < bVar1)) {
    return 0;
  }
  iVar4 = 0;
  *__s = '\0';
  __s_00 = (byte *)rstrtok(param_2,&local_20);
  if (__s_00 == (byte *)0x0) {
    return 0;
  }
  do {
    sVar2 = strlen((char *)__s_00);
    puVar3 = local_1e + iVar4;
    iVar4 = iVar4 + 1;
    if (sVar2 != 2) {
      return 0;
    }
    if (((&_ctype)[*__s_00] & 0x44) == 0) {
      return 0;
    }
    if (((&_ctype)[__s_00[1]] & 0x44) == 0) {
      return 0;
    }
    AtoH(__s_00,puVar3);
    __s_00 = (byte *)rstrtok(0,&local_20);
  } while (__s_00 != (byte *)0x0);
  if (iVar4 != 6) {
    return 0;
  }
  if (0 < DebugLevel) {
    printk("\n%02x:%02x:%02x:%02x:%02x:%02x-%02x\n",local_1e[0],local_1e[1],local_1e[2],local_1e[3],
           local_1a,local_19,bVar1);
  }
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    iVar4 = MacTableLookup(param_1,local_1e);
    if (*(char *)(param_1 + 0x286285) != '\0') goto LAB_000dd620;
  }
  else if (*(char *)(param_1 + 0x286285) != '\0') {
    return 1;
  }
  iVar4 = MacTableLookup2(param_1,local_1e,0);
LAB_000dd620:
  if (iVar4 != 0) {
    if (0 < DebugLevel) {
      printk("\nSetup BA Session: Tid = %d\n",bVar1);
    }
    ba_ori_session_setup(param_1,*(undefined2 *)(iVar4 + 0xe0),bVar1,0);
  }
  return 1;
}

