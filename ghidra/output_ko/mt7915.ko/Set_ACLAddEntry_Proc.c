// module: mt7915.ko
// function: Set_ACLAddEntry_Proc @ 0x2c94c
// size: 1344 bytes
//

undefined4 Set_ACLAddEntry_Proc(int *param_1,char *param_2)

{
  bool bVar1;
  char *__s;
  size_t sVar2;
  byte *__s_00;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  void *pvVar8;
  char *local_3c [2];
  void *local_34;
  undefined1 local_2e [4];
  undefined1 local_2a;
  undefined1 local_29;
  
  iVar6 = *param_1;
  local_34 = (void *)0x0;
  local_3c[0] = param_2;
  if (*(uint *)((int)param_1 + *(int *)(iVar6 + 0x3c) * 0x5834 + 0x2bb675) < 0x80) {
    os_alloc_mem(0,&local_34,0x408);
    if (local_34 != (void *)0x0) {
      __memzero(local_34,0x408);
      memmove(local_34,(void *)((int)param_1 + *(int *)(iVar6 + 0x3c) * 0x5834 + 0x2bb671),0x408);
      do {
        do {
          do {
            while( true ) {
              while( true ) {
                __s = strsep(local_3c,";");
                if (__s == (char *)0x0) goto LAB_0002cbd4;
                if (*__s != '\0') break;
                if (1 < DebugLevel) {
                  printk("An unnecessary delimiter entered!\n");
                }
              }
              sVar2 = strlen(__s);
              if (sVar2 == 0x11) break;
              if (-1 < DebugLevel) {
                printk("illegal MAC address length!\n");
              }
            }
            __s_00 = (byte *)rstrtok(__s,&_LC162);
          } while (__s_00 == (byte *)0x0);
          iVar3 = 0;
          do {
            sVar2 = strlen((char *)__s_00);
            if (((sVar2 != 2) || (((&_ctype)[*__s_00] & 0x44) == 0)) ||
               (((&_ctype)[__s_00[1]] & 0x44) == 0)) {
              iVar5 = iVar3;
              if (-1 < DebugLevel) {
                printk("illegal MAC address format or octet!\n");
              }
              break;
            }
            iVar5 = iVar3 + 1;
            AtoH(__s_00,local_2e + iVar3,1);
            __s_00 = (byte *)rstrtok(0,&_LC162);
            iVar3 = iVar5;
          } while (__s_00 != (byte *)0x0);
        } while (iVar5 != 6);
        pvVar8 = local_34;
        if (*(int *)((int)local_34 + 4) == 0) {
          iVar3 = 1;
LAB_0002cd44:
          *(int *)((int)pvVar8 + 4) = iVar3;
          memmove((void *)((int)pvVar8 + iVar3 * 8),local_2e,6);
          uVar4 = *(uint *)((int)local_34 + 4);
        }
        else {
          bVar1 = false;
          uVar7 = 0;
          do {
            uVar7 = uVar7 + 1;
            iVar3 = memcmp((void *)((int)pvVar8 + uVar7 * 8),local_2e,6);
            if (iVar3 == 0) {
              if (1 < DebugLevel) {
                bVar1 = true;
                printk("You have added an entry before :\n");
                pvVar8 = local_34;
                if (1 < DebugLevel) {
                  printk("The duplicate entry is %02x:%02x:%02x:%02x:%02x:%02x\n",local_2e[0],
                         local_2e[1],local_2e[2],local_2e[3],local_2a,local_29);
                  pvVar8 = local_34;
                  goto LAB_0002cb4c;
                }
              }
              bVar1 = true;
            }
LAB_0002cb4c:
            uVar4 = *(uint *)((int)pvVar8 + 4);
          } while (uVar7 < uVar4);
          if (!bVar1) {
            iVar3 = uVar4 + 1;
            goto LAB_0002cd44;
          }
        }
      } while (uVar4 != 0x80);
      if (1 < DebugLevel) {
        printk("The AccessControlList is full, and no more entry can join the list!\n");
        if (DebugLevel < 2) {
LAB_0002cbd4:
          uVar7 = *(uint *)((int)local_34 + 4);
        }
        else {
          printk("The last entry of ACL is %02x:%02x:%02x:%02x:%02x:%02x\n",local_2e[0],local_2e[1],
                 local_2e[2],local_2e[3],local_2a,local_29);
          uVar7 = *(uint *)((int)local_34 + 4);
        }
        if (0x80 < uVar7) {
          printk(&_LC227,0x2c43);
          dump_stack();
        }
      }
      __memzero((char *)((int)param_1 +
                        (int)("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM5\n" +
                             *(int *)(iVar6 + 0x3c) * 0x5834 + 0x31)),0x408);
      memmove((void *)((int)param_1 + *(int *)(iVar6 + 0x3c) * 0x5834 + 0x2bb671),local_34,0x408);
      ApUpdateAccessControlList(param_1,*(undefined1 *)(iVar6 + 0x3c));
      if ((2 < DebugLevel) &&
         (printk("Set::%s(Policy=%d, Entry#=%d)\n","Set_ACLAddEntry_Proc",
                 *(undefined4 *)((int)param_1 + *(int *)(iVar6 + 0x3c) * 0x5834 + 0x2bb671),
                 *(undefined4 *)((int)param_1 + *(int *)(iVar6 + 0x3c) * 0x5834 + 0x2bb675)),
         2 < DebugLevel)) {
        printk("=============== Entry ===============\n");
      }
      if (*(int *)((int)param_1 + *(int *)(iVar6 + 0x3c) * 0x5834 + 0x2bb675) != 0) {
        uVar7 = 1;
        do {
          if (2 < DebugLevel) {
            printk("Entry #%02d: ",uVar7);
          }
          iVar5 = 0;
          iVar3 = DebugLevel;
          do {
            if (2 < iVar3) {
              printk("%02X ",*(char *)((int)param_1 +
                                      (int)("Set::OID_802_11_NETWORK_TYPE_IN_USE (=%d)\n" +
                                           iVar5 + *(int *)(iVar6 + 0x3c) * 0x5834 + (uVar7 - 1) * 8
                                           + 5)));
              iVar3 = DebugLevel;
            }
            iVar5 = iVar5 + 1;
          } while (iVar5 != 6);
          if (2 < iVar3) {
            printk(&_LC220);
          }
          bVar1 = uVar7 < *(uint *)((int)param_1 + *(int *)(iVar6 + 0x3c) * 0x5834 + 0x2bb675);
          uVar7 = uVar7 + 1;
        } while (bVar1);
      }
      if (local_34 != (void *)0x0) {
        os_free_mem();
      }
      return 1;
    }
    if (-1 < DebugLevel) {
      printk("%s: Allocate memory fail!!!\n","Set_ACLAddEntry_Proc");
    }
  }
  else if (1 < DebugLevel) {
    printk("The AccessControlList is full, and no more entry can join the list!\n");
  }
  return 0;
}

