// module: mt7915.ko
// function: ZTE_Sta_Blacklist_Del @ 0x160e44
// size: 840 bytes
//

void * ZTE_Sta_Blacklist_Del(int *param_1,char *param_2)

{
  char *__s;
  size_t sVar1;
  byte *__s_00;
  int iVar2;
  void *pvVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *__s1;
  int iVar6;
  uint uVar7;
  uint uVar8;
  char *local_3c;
  undefined4 *local_38;
  undefined1 local_34 [4];
  undefined1 local_30;
  undefined1 local_2f;
  undefined1 auStack_2e [10];
  
  local_38 = (undefined4 *)0x0;
  iVar6 = *param_1;
  local_3c = param_2;
  os_alloc_mem(0,&local_38,0x408);
  if (local_38 == (undefined4 *)0x0) {
    pvVar3 = (void *)0x0;
    if (-1 < DebugLevel) {
      printk("%s: Allocate memory fail!!!\n","ZTE_Sta_Blacklist_Del");
    }
  }
  else {
    __memzero(local_38,0x408);
    memmove(local_38,(void *)((int)param_1 + *(int *)(iVar6 + 0x3c) * 0x5834 + 0x2bc2b2),0x408);
    __memzero(auStack_2e,6);
LAB_00160ecc:
    __s = strsep(&local_3c,";");
    if (__s != (char *)0x0) {
      if (((*__s != '\0') && (sVar1 = strlen(__s), sVar1 == 0x11)) &&
         (__s_00 = (byte *)rstrtok(__s,&_LC2), __s_00 != (byte *)0x0)) {
        iVar2 = 0;
        do {
          sVar1 = strlen((char *)__s_00);
          iVar4 = iVar2;
          if (((sVar1 != 2) || (((&_ctype)[*__s_00] & 0x44) == 0)) ||
             (((&_ctype)[__s_00[1]] & 0x44) == 0)) break;
          iVar4 = iVar2 + 1;
          AtoH(__s_00,local_34 + iVar2);
          __s_00 = (byte *)rstrtok(0,&_LC2);
          iVar2 = iVar4;
        } while (__s_00 != (byte *)0x0);
        if (iVar4 == 6) {
          if (local_38[1] != 0) {
            uVar7 = 0;
            puVar5 = local_38;
            uVar8 = uVar7;
            do {
              uVar7 = uVar7 + 1;
              iVar2 = memcmp(puVar5 + uVar7 * 2,local_34,6);
              if (iVar2 == 0) {
                __memzero(puVar5 + uVar7 * 2,6);
                uVar8 = 1;
                puVar5 = local_38;
                if (2 < DebugLevel) {
                  printk("The entry %02x:%02x:%02x:%02x:%02x:%02x founded will be deleted!\n",
                         local_34[0],local_34[1],local_34[2],local_34[3],local_30,local_2f);
                  puVar5 = local_38;
                }
              }
            } while (uVar7 < (uint)puVar5[1]);
            if (uVar8 != 0) goto LAB_00160ecc;
          }
          if (2 < DebugLevel) {
            printk("The entry %02x:%02x:%02x:%02x:%02x:%02x is not in the list!\n",local_34[0],
                   local_34[1],local_34[2],local_34[3],local_30,local_2f);
          }
        }
      }
      goto LAB_00160ecc;
    }
    pvVar3 = (void *)__memzero((char *)((int)param_1 +
                                       (int)("Query::OID_802_11_STATISTICS(mem alloc failed)\n" +
                                            *(int *)(iVar6 + 0x3c) * 0x5834 + 0x26)),0x408);
    puVar5 = local_38;
    *(undefined4 *)((int)param_1 + *(int *)(iVar6 + 0x3c) * 0x5834 + 0x2bc2b2) = *local_38;
    uVar8 = local_38[1];
    iVar2 = 0;
    if (uVar8 != 0) {
      uVar7 = 0;
      __s1 = local_38 + 2;
      iVar2 = 0;
      do {
        while( true ) {
          uVar7 = uVar7 + 1;
          iVar4 = memcmp(__s1,auStack_2e,6);
          if (iVar4 == 0) break;
          iVar4 = iVar2 + 1;
          pvVar3 = memmove((char *)((int)param_1 +
                                   (int)("Query::OID_802_11_STATISTICS(mem alloc failed)\n" +
                                        *(int *)(iVar6 + 0x3c) * 0x5834 + iVar2 * 8 + 0x2e)),__s1,6)
          ;
          uVar8 = puVar5[1];
          __s1 = __s1 + 2;
          iVar2 = iVar4;
          if (uVar8 <= uVar7) goto LAB_001610e4;
        }
        __s1 = __s1 + 2;
        pvVar3 = (void *)0x0;
      } while (uVar7 < uVar8);
    }
LAB_001610e4:
    if (puVar5 == (undefined4 *)0x0) {
      pvVar3 = (void *)0x1;
    }
    *(int *)((int)param_1 + *(int *)(iVar6 + 0x3c) * 0x5834 + 0x2bc2b6) = iVar2;
    if (puVar5 != (undefined4 *)0x0) {
      os_free_mem(puVar5);
      pvVar3 = (void *)0x1;
    }
  }
  return pvVar3;
}

