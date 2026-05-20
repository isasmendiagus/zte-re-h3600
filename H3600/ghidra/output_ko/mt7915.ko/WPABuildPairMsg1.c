// module: mt7915.ko
// function: WPABuildPairMsg1 @ 0x11e890
// size: 1736 bytes
//

void WPABuildPairMsg1(int param_1,uint *param_2,int *param_3)

{
  ushort uVar1;
  int iVar2;
  char cVar3;
  uint uVar4;
  int iVar5;
  uint *puVar6;
  size_t __n;
  int iVar7;
  undefined4 *__src;
  uint uVar8;
  bool bVar9;
  int local_9c;
  int local_90;
  char local_8c [8];
  uint local_84;
  undefined2 local_80;
  undefined4 local_7e;
  undefined2 local_7a;
  undefined4 local_78;
  uint local_72;
  undefined2 local_6e;
  undefined2 local_6c;
  
  if (2 < DebugLevel) {
    printk("===> %s\n","WPABuildPairMsg1");
  }
  if ((*(uint *)(param_1 + 0xa39f84) & 0x40) != 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("[ERROR]%s : The interface is closed...\n","WPABuildPairMsg1");
    return;
  }
  if ((param_3 == (int *)0x0) || (*param_3 == 0)) {
    if (DebugLevel < 0) {
      return;
    }
    printk("[ERROR]%s : The entry doesn\'t exist.\n","WPABuildPairMsg1");
    return;
  }
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    iVar5 = param_3[2];
    if (iVar5 != *(int *)(iVar5 + 4)) {
      if (DebugLevel < 0) {
        return;
      }
      printk("[ERROR]%s : cannot get binding wdev(%p).\n","WPABuildPairMsg1",iVar5);
      return;
    }
    if ((byte)param_2[0xe6] - 6 < 3) {
      iVar7 = memcmp(param_3 + 0x3b,(void *)(iVar5 + 0x2f39),6);
      iVar2 = DebugLevel;
      if ((iVar7 == 0) && (*(char *)(iVar5 + 0x2f36) != '\0')) {
        *(undefined1 *)(param_2 + 0xe6) = 0;
        if (iVar2 < 0) {
          return;
        }
        printk("This is a WSC-Enrollee. Not expect calling WPAStart4WayHS here\n");
        return;
      }
      goto LAB_0011e98c;
    }
  }
  else if ((byte)param_2[0xe6] - 6 < 3) {
LAB_0011e98c:
    uVar4 = 8;
    do {
      uVar4 = uVar4 - 1 & 0xff;
      cVar3 = *(char *)((int)param_2 + uVar4 + 0x390) + '\x01';
      *(char *)((int)param_2 + uVar4 + 0x390) = cVar3;
    } while (uVar4 != 0 && cVar3 == '\0');
    puVar6 = param_2 + 0xc9;
    GenRandom(param_1,puVar6,param_2 + 0xcc);
    os_alloc_mem(0,&local_90,0x5dc);
    iVar5 = local_90;
    if (local_90 != 0) {
      __memzero(local_90,0x5dc);
      *(undefined1 *)((int)param_2 + 0x39a) = 1;
      WPAConstructEapolMsg(param_3,1,param_2,param_3[2] + 0x2c,iVar5);
      if (((*param_2 & 0x10040) == 0) || (iVar2 = is_pmkid_cache_in_sec_config(param_2), iVar2 == 0)
         ) {
        if (((*param_2 & 0x2000) == 0) || (*(char *)((int)param_2 + 0x3e6) != '\x01')) {
          __src = &local_78;
        }
        else {
          if ((*param_2 & 0x30000) == 0) {
            if ((char)param_2[0xa1] == '\x02') {
              local_9c = 0x18;
            }
            else {
              local_9c = 0x10;
            }
          }
          else {
            local_9c = 0x18;
          }
          iVar7 = iVar5 + local_9c + 0x48;
          *(undefined1 *)(iVar7 + 0xb) = 0xdd;
          *(undefined1 *)(iVar7 + 0xd) = 0;
          *(undefined1 *)(iVar7 + 0xe) = 0xf;
          *(undefined1 *)(iVar7 + 0xf) = 0xac;
          *(undefined1 *)(iVar7 + 0x10) = 4;
          iVar2 = is_pmkid_cache_in_sec_config(param_2);
          if (iVar2 == 0) {
            local_7e = *(undefined4 *)((int)param_2 + 0x32a);
            __src = (undefined4 *)*param_2;
            builtin_strncpy(local_8c,"PMK Name",8);
            bVar9 = ((uint)__src & 0x6000) == 0;
            local_7a = *(undefined2 *)((int)param_2 + 0x32e);
            if (bVar9) {
              __src = &local_78;
            }
            local_84 = *puVar6;
            local_80 = (undefined2)param_2[0xca];
            if (!bVar9) {
              if (2 < DebugLevel) {
                printk("%s:[SAE]pmkid not found\n","WPABuildPairMsg1");
              }
              __src = &local_78;
              iVar2 = sae_get_pmk_cache("pci_sw_int_handler" + param_1,puVar6,
                                        (undefined4 *)((int)param_2 + 0x32a),__src,0);
              if (iVar2 == 0) {
                if (-1 < DebugLevel) {
                  printk("%s: derive pmkid fail\n","WPABuildPairMsg1");
                }
                os_free_mem(local_90);
                return;
              }
            }
            memmove((void *)(iVar7 + 0x11),__src,0x10);
          }
          else {
            memmove((void *)(iVar7 + 0x11),(void *)param_2[0x163],0x10);
            memmove((void *)((int)param_2 + 0x18e),(void *)param_2[0x164],0x20);
            if (DebugLevel < 3) {
              __src = &local_78;
            }
            else {
              printk("%s: PMKID found for WPA2PSK/WPA3PSK\n","WPABuildPairMsg1");
              __src = &local_78;
            }
          }
          *(undefined1 *)(iVar7 + 0xc) = 0x14;
          uVar4 = CONCAT11(*(undefined1 *)(iVar5 + local_9c + 0x51),*(undefined1 *)(iVar7 + 10)) +
                  0x16 & 0xffff;
          *(char *)(iVar5 + local_9c + 0x51) = (char)(uVar4 >> 8);
          *(char *)(iVar7 + 10) = (char)uVar4;
          uVar4 = CONCAT11(*(undefined1 *)(iVar5 + 2),*(undefined1 *)(iVar5 + 3)) + 0x16 & 0xffff;
          *(char *)(iVar5 + 3) = (char)uVar4;
          *(char *)(iVar5 + 2) = (char)(uVar4 >> 8);
        }
      }
      else {
        if (2 < DebugLevel) {
          printk("===> %s      Add PMKID\n","WPABuildPairMsg1");
        }
        if ((*param_2 & 0x30000) == 0) {
          if ((char)param_2[0xa1] == '\x02') {
            __n = 0x30;
            local_9c = 0x18;
          }
          else {
            __n = 0x20;
            local_9c = 0x10;
          }
        }
        else {
          __n = 0x30;
          local_9c = 0x18;
        }
        hex_dump("PMKID",param_2[0x163],0x10);
        hex_dump(&_LC143,param_2[0x164],__n);
        iVar2 = iVar5 + local_9c + 0x48;
        *(undefined1 *)(iVar2 + 0xb) = 0xdd;
        *(undefined1 *)(iVar2 + 0xd) = 0;
        *(undefined1 *)(iVar2 + 0xe) = 0xf;
        *(undefined1 *)(iVar2 + 0xf) = 0xac;
        __src = &local_78;
        *(undefined1 *)(iVar2 + 0x10) = 4;
        memmove((void *)(iVar2 + 0x11),(void *)param_2[0x163],0x10);
        memmove((void *)((int)param_2 + 0x18e),(void *)param_2[0x164],__n);
        *(undefined1 *)(iVar2 + 0xc) = 0x14;
        uVar4 = CONCAT11(*(undefined1 *)(iVar5 + local_9c + 0x51),*(undefined1 *)(iVar2 + 10)) +
                0x16 & 0xffff;
        *(char *)(iVar5 + local_9c + 0x51) = (char)(uVar4 >> 8);
        *(char *)(iVar2 + 10) = (char)uVar4;
        uVar4 = CONCAT11(*(undefined1 *)(iVar5 + 2),*(undefined1 *)(iVar5 + 3)) + 0x16 & 0xffff;
        *(char *)(iVar5 + 3) = (char)uVar4;
        *(char *)(iVar5 + 2) = (char)(uVar4 >> 8);
      }
      local_78 = *(undefined4 *)((int)param_2 + 0x32a);
      uVar8 = *puVar6;
      uVar4 = param_2[0xca];
      uVar1 = *(ushort *)(param_3 + 0x38);
      *(undefined2 *)(__src + 1) = *(undefined2 *)((int)param_2 + 0x32e);
      local_6c = EAPOL;
      local_72 = uVar8;
      local_6e = (short)uVar4;
      RTMPToWirelessSta(param_1,param_3,__src,0xe,iVar5,
                        CONCAT11(*(undefined1 *)(iVar5 + 2),*(undefined1 *)(iVar5 + 3)) + 4,
                        *(char *)(param_1 + (uint)uVar1 * 0x620 + 0x2f762) != '\x01');
      RTMPModTimer(param_2 + 0xe9,1000);
      *(undefined1 *)((int)param_2 + 0x399) = 0;
      *(undefined1 *)(param_2 + 0xe6) = 8;
      os_free_mem(local_90);
      if (2 < DebugLevel) {
        printk("<=== %s: send Msg1 of 4-way\n","WPABuildPairMsg1");
      }
      __ZTE_STA_Assoc_Process(param_1,5,0,0,0,0,param_3,"WPABuildPairMsg1",0x12b4);
      return;
    }
    if (DebugLevel < 0) {
      return;
    }
    printk("!!!%s : no memory!!!\n","WPABuildPairMsg1");
    return;
  }
  if (-1 < DebugLevel) {
    printk("[ERROR]%s : Not expect calling\n","WPABuildPairMsg1");
  }
  return;
}

