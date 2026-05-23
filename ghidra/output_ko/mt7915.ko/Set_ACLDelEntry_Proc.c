// module: mt7915.ko
// function: Set_ACLDelEntry_Proc @ 0x2ce90
// size: 1432 bytes
//

undefined4 Set_ACLDelEntry_Proc(int *param_1,char *param_2)

{
  char *__s;
  size_t sVar1;
  int iVar2;
  undefined4 uVar3;
  byte *__s_00;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined4 *__s1;
  uint uVar8;
  uint uVar9;
  bool bVar10;
  char *local_3c;
  undefined4 *local_38;
  undefined1 local_34 [4];
  undefined1 local_30;
  undefined1 local_2f;
  undefined1 auStack_2e [10];
  
  local_38 = (undefined4 *)0x0;
  iVar7 = *param_1;
  local_3c = param_2;
  os_alloc_mem(0,&local_38,0x408);
  if (local_38 == (undefined4 *)0x0) {
    uVar3 = 0;
    if (-1 < DebugLevel) {
      printk("%s: Allocate memory fail!!!\n","Set_ACLDelEntry_Proc");
    }
  }
  else {
    __memzero(local_38,0x408);
    memmove(local_38,(void *)((int)param_1 + *(int *)(iVar7 + 0x3c) * 0x5834 + 0x2bb671),0x408);
    __memzero(auStack_2e,6);
LAB_0002cf18:
    __s = strsep(&local_3c,";");
    if (__s != (char *)0x0) {
      if (*__s == '\0') {
        if (1 < DebugLevel) {
          printk("An unnecessary delimiter entered!\n");
        }
      }
      else {
        sVar1 = strlen(__s);
        if (sVar1 == 0x11) {
          __s_00 = (byte *)rstrtok(__s,&_LC162);
          if (__s_00 != (byte *)0x0) {
            iVar4 = 0;
            do {
              sVar1 = strlen((char *)__s_00);
              if (((sVar1 != 2) || (((&_ctype)[*__s_00] & 0x44) == 0)) ||
                 (((&_ctype)[__s_00[1]] & 0x44) == 0)) {
                iVar5 = iVar4;
                if (-1 < DebugLevel) {
                  printk("illegal MAC address format or octet!\n");
                }
                break;
              }
              iVar5 = iVar4 + 1;
              AtoH(__s_00,local_34 + iVar4,1);
              __s_00 = (byte *)rstrtok(0,&_LC162);
              iVar4 = iVar5;
            } while (__s_00 != (byte *)0x0);
            if (iVar5 == 6) {
              if (local_38[1] != 0) {
                uVar8 = 0;
                puVar6 = local_38;
                uVar9 = uVar8;
                do {
                  uVar8 = uVar8 + 1;
                  iVar4 = memcmp(puVar6 + uVar8 * 2,local_34,6);
                  if (iVar4 == 0) {
                    __memzero(puVar6 + uVar8 * 2,6);
                    uVar9 = 1;
                    puVar6 = local_38;
                    if (2 < DebugLevel) {
                      printk("The entry %02x:%02x:%02x:%02x:%02x:%02x founded will be deleted!\n",
                             local_34[0],local_34[1],local_34[2],local_34[3],local_30,local_2f);
                      puVar6 = local_38;
                    }
                  }
                } while (uVar8 < (uint)puVar6[1]);
                if (uVar9 != 0) goto LAB_0002cf18;
              }
              if (2 < DebugLevel) {
                printk("The entry %02x:%02x:%02x:%02x:%02x:%02x is not in the list!\n",local_34[0],
                       local_34[1],local_34[2],local_34[3],local_30,local_2f);
              }
            }
          }
        }
        else if (-1 < DebugLevel) {
          printk("illegal MAC address length!\n");
        }
      }
      goto LAB_0002cf18;
    }
    __memzero((char *)((int)param_1 +
                      (int)("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM5\n" +
                           *(int *)(iVar7 + 0x3c) * 0x5834 + 0x31)),0x408);
    *(undefined4 *)((int)param_1 + *(int *)(iVar7 + 0x3c) * 0x5834 + 0x2bb671) = *local_38;
    iVar4 = *(int *)(iVar7 + 0x3c);
    if (*(int *)((int)param_1 + iVar4 * 0x5834 + 0x2bb675) != 0) {
      printk(&_LC233,0x2cb5);
      dump_stack();
      iVar4 = *(int *)(iVar7 + 0x3c);
    }
    puVar6 = local_38;
    uVar9 = local_38[1];
    iVar5 = 0;
    if (uVar9 != 0) {
      uVar8 = 0;
      iVar5 = 0;
      __s1 = local_38 + 2;
      do {
        while( true ) {
          uVar8 = uVar8 + 1;
          iVar2 = memcmp(__s1,auStack_2e,6);
          if (iVar2 == 0) break;
          iVar2 = iVar5 + 1;
          memmove((char *)((int)param_1 +
                          (int)("Set::OID_802_11_NETWORK_TYPE_IN_USE (=%d)\n" +
                               iVar4 * 0x5834 + iVar5 * 8 + 5)),__s1,8);
          iVar4 = *(int *)(iVar7 + 0x3c);
          uVar9 = puVar6[1];
          iVar5 = iVar2;
          __s1 = __s1 + 2;
          if (uVar9 <= uVar8) goto LAB_0002d07c;
        }
        __s1 = __s1 + 2;
      } while (uVar8 < uVar9);
    }
LAB_0002d07c:
    *(int *)((int)param_1 + iVar4 * 0x5834 + 0x2bb675) = iVar5;
    uVar9 = *(uint *)(iVar7 + 0x3c);
    if ((uint)puVar6[1] < *(uint *)((int)param_1 + uVar9 * 0x5834 + 0x2bb675)) {
      printk(&_LC234,0x2cc0);
      dump_stack();
      uVar9 = *(uint *)(iVar7 + 0x3c);
    }
    ApUpdateAccessControlList(param_1,uVar9 & 0xff);
    if ((2 < DebugLevel) &&
       (printk("Set::%s(Policy=%u, Entry#=%u)\n","Set_ACLDelEntry_Proc",
               *(undefined4 *)((int)param_1 + *(int *)(iVar7 + 0x3c) * 0x5834 + 0x2bb671),
               *(undefined4 *)((int)param_1 + *(int *)(iVar7 + 0x3c) * 0x5834 + 0x2bb675)),
       2 < DebugLevel)) {
      printk("=============== Entry ===============\n");
    }
    if (*(int *)((int)param_1 + *(int *)(iVar7 + 0x3c) * 0x5834 + 0x2bb675) != 0) {
      uVar9 = 1;
      do {
        if (2 < DebugLevel) {
          printk("Entry #%02d: ",uVar9);
        }
        iVar5 = 0;
        iVar4 = DebugLevel;
        do {
          if (2 < iVar4) {
            printk("%02X ",*(char *)((int)param_1 +
                                    (int)("Set::OID_802_11_NETWORK_TYPE_IN_USE (=%d)\n" +
                                         iVar5 + *(int *)(iVar7 + 0x3c) * 0x5834 + (uVar9 - 1) * 8 +
                                         5)));
            iVar4 = DebugLevel;
          }
          iVar5 = iVar5 + 1;
        } while (iVar5 != 6);
        if (2 < iVar4) {
          printk(&_LC220);
        }
        bVar10 = uVar9 < *(uint *)((int)param_1 + *(int *)(iVar7 + 0x3c) * 0x5834 + 0x2bb675);
        uVar9 = uVar9 + 1;
      } while (bVar10);
    }
    os_free_mem(local_38);
    uVar3 = 1;
  }
  return uVar3;
}

