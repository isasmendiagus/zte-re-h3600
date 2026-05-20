// module: mt7915.ko
// function: Set_BARecTearDown_Proc @ 0xdd9c8
// size: 708 bytes
//

undefined4 Set_BARecTearDown_Proc(int param_1,char *param_2)

{
  byte bVar1;
  ushort uVar2;
  size_t sVar3;
  char *pcVar4;
  byte *__s;
  undefined1 *puVar5;
  int iVar6;
  undefined2 local_20;
  undefined1 local_1e [4];
  undefined1 local_1a;
  undefined1 local_19;
  
  local_20 = 0x3a;
  sVar3 = strlen(param_2);
  if (sVar3 < 0x13) {
    pcVar4 = strchr(param_2,0x2d);
    if ((pcVar4 != (char *)0x0) && (sVar3 = strlen(pcVar4), 1 < sVar3)) {
      bVar1 = os_str_tol(pcVar4 + 1,0,10);
      if (bVar1 < 8) {
        *pcVar4 = '\0';
        uVar2 = os_str_tol(param_2,0,10);
        if (uVar2 < 0x80) {
          if (0 < DebugLevel) {
            printk("tear down rec ba,wcid=%d,tid=%d\n\r",uVar2,bVar1);
          }
          ba_rec_session_tear_down(param_1,uVar2,bVar1,0);
          return 1;
        }
        if (0 < DebugLevel) {
          printk("wcid=%d is wrong\n\r",uVar2);
          return 0;
        }
      }
      else if (0 < DebugLevel) {
        printk("tid=%d is wrong\n\r",bVar1);
      }
    }
    return 0;
  }
  pcVar4 = strchr(param_2,0x2d);
  if (pcVar4 == (char *)0x0) {
    return 0;
  }
  sVar3 = strlen(pcVar4);
  if (sVar3 < 2) {
    return 0;
  }
  bVar1 = os_str_tol(pcVar4 + 1,0,10);
  if (7 < bVar1) {
    return 0;
  }
  iVar6 = 0;
  *pcVar4 = '\0';
  __s = (byte *)rstrtok(param_2,&local_20);
  if (__s == (byte *)0x0) {
    return 0;
  }
  do {
    sVar3 = strlen((char *)__s);
    puVar5 = local_1e + iVar6;
    iVar6 = iVar6 + 1;
    if (sVar3 != 2) {
      return 0;
    }
    if (((&_ctype)[*__s] & 0x44) == 0) {
      return 0;
    }
    if (((&_ctype)[__s[1]] & 0x44) == 0) {
      return 0;
    }
    AtoH(__s,puVar5);
    __s = (byte *)rstrtok(0,&local_20);
  } while (__s != (byte *)0x0);
  if (iVar6 != 6) {
    return 0;
  }
  if (0 < DebugLevel) {
    printk("\n%02x:%02x:%02x:%02x:%02x:%02x-%02x",local_1e[0],local_1e[1],local_1e[2],local_1e[3],
           local_1a,local_19,bVar1);
  }
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    iVar6 = MacTableLookup(param_1,local_1e);
    if (*(char *)(param_1 + 0x286285) != '\0') goto LAB_000ddc00;
  }
  else if (*(char *)(param_1 + 0x286285) != '\0') {
    return 1;
  }
  iVar6 = MacTableLookup2(param_1,local_1e,0);
LAB_000ddc00:
  if (iVar6 != 0) {
    if (0 < DebugLevel) {
      printk("\nTear down Rec BA Session: Tid = %d\n",bVar1);
    }
    ba_rec_session_tear_down(param_1,*(undefined2 *)(iVar6 + 0xe0),bVar1,0);
  }
  return 1;
}

