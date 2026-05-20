// module: mt7915.ko
// function: ZTE_Sta_Blacklist_Add @ 0x160b34
// size: 784 bytes
//

undefined4 ZTE_Sta_Blacklist_Add(int *param_1,char *param_2)

{
  bool bVar1;
  char *__s;
  size_t sVar2;
  byte *__s_00;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  void *pvVar8;
  char *local_3c [2];
  void *local_34;
  undefined1 auStack_2e [10];
  
  iVar7 = *param_1;
  local_34 = (void *)0x0;
  local_3c[0] = param_2;
  if (0x7e < *(uint *)((int)param_1 + *(int *)(iVar7 + 0x3c) * 0x5834 + 0x2bc2b6)) {
    if (DebugLevel < 2) {
      return 0;
    }
    printk("The MapBlackList is full, and no more entry can join the list!\n");
    return 0;
  }
  os_alloc_mem(0,&local_34,0x408);
  if (local_34 == (void *)0x0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: Allocate memory fail!!!\n","ZTE_Sta_Blacklist_Add");
    return 0;
  }
  __memzero(local_34,0x408);
  memmove(local_34,(void *)((int)param_1 + *(int *)(iVar7 + 0x3c) * 0x5834 + 0x2bc2b2),0x408);
  do {
    do {
      do {
        __s = strsep(local_3c,";");
        if (__s == (char *)0x0) goto LAB_00160d4c;
      } while (((*__s == '\0') || (sVar2 = strlen(__s), sVar2 != 0x11)) ||
              (__s_00 = (byte *)rstrtok(__s,&_LC2), __s_00 == (byte *)0x0));
      iVar3 = 0;
      do {
        sVar2 = strlen((char *)__s_00);
        iVar6 = iVar3;
        if (((sVar2 != 2) || (((&_ctype)[*__s_00] & 0x44) == 0)) ||
           (((&_ctype)[__s_00[1]] & 0x44) == 0)) break;
        iVar6 = iVar3 + 1;
        AtoH(__s_00,auStack_2e + iVar3);
        __s_00 = (byte *)rstrtok(0,&_LC2);
        iVar3 = iVar6;
      } while (__s_00 != (byte *)0x0);
    } while (iVar6 != 6);
    pvVar8 = local_34;
    if (*(int *)((int)local_34 + 4) == 0) {
      iVar3 = 1;
LAB_00160dfc:
      *(int *)((int)pvVar8 + 4) = iVar3;
      memmove((void *)((int)pvVar8 + iVar3 * 8),auStack_2e,6);
      uVar4 = *(uint *)((int)local_34 + 4);
    }
    else {
      bVar1 = false;
      uVar5 = 0;
      do {
        uVar5 = uVar5 + 1;
        iVar3 = memcmp((void *)((int)pvVar8 + uVar5 * 8),auStack_2e,6);
        if ((iVar3 == 0) && (bVar1 = true, 1 < DebugLevel)) {
          printk("You have added an entry before :\n");
          pvVar8 = local_34;
        }
        uVar4 = *(uint *)((int)pvVar8 + 4);
      } while (uVar5 < uVar4);
      if (!bVar1) {
        iVar3 = uVar4 + 1;
        goto LAB_00160dfc;
      }
    }
  } while (uVar4 != 0x80);
  if (1 < DebugLevel) {
    printk("The MapBlackList is full, and no more entry can join the list!\n");
LAB_00160d4c:
    if (*(uint *)((int)local_34 + 4) < 0x80) goto LAB_00160d5c;
  }
  printk(&_LC8,0x172);
  dump_stack();
LAB_00160d5c:
  __memzero((char *)((int)param_1 +
                    (int)("Query::OID_802_11_STATISTICS(mem alloc failed)\n" +
                         *(int *)(iVar7 + 0x3c) * 0x5834 + 0x26)),0x408);
  pvVar8 = local_34;
  memmove((void *)((int)param_1 + *(int *)(iVar7 + 0x3c) * 0x5834 + 0x2bc2b2),local_34,0x408);
  if (pvVar8 != (void *)0x0) {
    os_free_mem(pvVar8);
    return 1;
  }
  return 1;
}

