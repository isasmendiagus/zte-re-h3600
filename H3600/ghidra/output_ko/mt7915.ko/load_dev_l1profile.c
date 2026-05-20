// module: mt7915.ko
// function: load_dev_l1profile @ 0x14f1c8
// size: 1608 bytes
//

size_t load_dev_l1profile(int param_1)

{
  char cVar1;
  void *pvVar2;
  int iVar3;
  size_t sVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  bool bVar9;
  char *pcVar10;
  size_t sVar11;
  char *pcVar12;
  void *local_80;
  int local_7c;
  char *local_78;
  int local_74;
  int local_70;
  short local_6c;
  char local_6a [10];
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  int local_50;
  int local_4c;
  char acStack_46 [34];
  
  local_80 = (void *)0x0;
  os_alloc_mem(param_1,&local_80,0x8000);
  if (local_80 == (void *)0x0) {
    if (-1 < DebugLevel) {
      printk("No enough memory\n");
      return 1;
    }
    return 1;
  }
  os_zero_mem(local_80,0x8000);
  os_file_open(&local_60,"/etc/wireless/mt7915/l1profile.dat",0,0);
  iVar3 = local_4c;
  iVar6 = local_50;
  if (local_50 == 0) {
    if (2 < DebugLevel) {
      printk("Open file \"%s\" Succeed!\n","/etc/wireless/mt7915/l1profile.dat");
    }
    if (iVar3 == 0) {
      iVar8 = 0x7fff;
    }
    else {
      uVar7 = iVar3 + 1;
      if (uVar7 < 0x8000) {
        uVar7 = 0x8000;
      }
      iVar8 = uVar7 - 1;
    }
    local_50 = 0;
    sVar4 = os_file_read(local_60,uStack_5c,uStack_58,uStack_54,0,local_4c,local_80,iVar8);
    if (sVar4 != 0) {
      if (2 < DebugLevel) {
        printk("Read file \"%s\"(%d) succeed!\n","/etc/wireless/mt7915/l1profile.dat",sVar4);
      }
      goto LAB_0014f304;
    }
    if (0 < DebugLevel) goto LAB_0014f760;
    sVar4 = 1;
    goto LAB_0014f614;
  }
  if (1 < DebugLevel) {
    printk("Open file \"%s\" failed, try embedded default!\n","/etc/wireless/mt7915/l1profile.dat");
  }
  sVar4 = strlen(l1profile_default);
  memcpy(local_80,l1profile_default,sVar4 + 1);
  if (sVar4 != 0) {
LAB_0014f304:
    local_7c = 0;
    memset(acStack_46,0,0x1e);
    pvVar2 = local_80;
    cVar1 = _LANCHOR0;
    iVar8 = (int)_LANCHOR0;
    pcVar10 = "Get_System_CapNode_Info" + param_1 + 4;
    pcVar10[0] = '\0';
    pcVar10[1] = '\0';
    pcVar10[2] = '\0';
    pcVar10[3] = '\0';
    if (iVar8 != 0) goto LAB_0014f4bc;
    local_6c = (short)cVar1;
    local_74 = iVar8;
    local_70 = iVar8;
    sprintf((char *)&local_74,"MT%x",*(undefined4 *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc));
    if (((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7615) &&
       ("rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x1e] == '\"')) {
      sVar11 = strlen((char *)&local_74);
      *(undefined2 *)((int)&local_74 + sVar11) = 0x41;
    }
    iVar8 = 0;
    local_78 = (char *)0x0;
    local_6a[0] = '\0';
    local_6a[1] = '\0';
    local_6a[2] = '\0';
    local_6a[3] = '\0';
    local_6a[4] = '\0';
    local_6a[5] = '\0';
    local_6a[6] = '\0';
    local_6a[7] = '\0';
    local_6a[8] = '\0';
    local_6a[9] = '\0';
    os_alloc_mem(0,&local_78,0x800);
    if (local_78 != (char *)0x0) {
      while( true ) {
        sprintf(local_6a,"INDEX%d",iVar8);
        iVar5 = RTMPGetKeyParameter(local_6a,local_78,0x800,pvVar2,1);
        pcVar10 = local_78;
        if (iVar5 == 0) break;
        sVar11 = strlen((char *)&local_74);
        iVar5 = strncmp(pcVar10,(char *)&local_74,sVar11);
        if (iVar5 == 0) {
          if (3 < DebugLevel) {
            printk("%s found as %s\n",&local_74,local_6a);
          }
          pcVar10 = &_LANCHOR0;
          while( true ) {
            pcVar12 = pcVar10 + 0x17c;
            if ((*pcVar10 != '\0') && (iVar5 = strcmp(pcVar10,local_6a), iVar5 == 0)) break;
            pcVar10 = pcVar12;
            if (pcVar12 == s_profile_path_0033ae50) {
              bVar9 = false;
              pcVar10 = "Get_System_CapNode_Info" + param_1 + 4;
              pcVar10[0] = '\0';
              pcVar10[1] = '\0';
              pcVar10[2] = '\0';
              pcVar10[3] = '\0';
              strcpy(&_LANCHOR0,local_6a);
              goto LAB_0014f48c;
            }
          }
          if (2 < DebugLevel) {
            printk("%s for %s occupied, next\n",local_6a,&local_74);
          }
        }
        else if (2 < DebugLevel) {
          printk("%s mismatch with %s as %s\n",&local_74,pcVar10,local_6a);
        }
        iVar8 = iVar8 + 1;
        if (iVar8 == 10) goto code_r0x0014f464;
      }
      if (2 < DebugLevel) {
        printk("%s not found, dismissed.\n",local_6a);
      }
      os_free_mem(local_78);
    }
    goto LAB_0014f67c;
  }
  if (0 < DebugLevel) {
LAB_0014f760:
    sVar4 = 1;
    printk("Read file \"%s\" failed(errCode=%d)!\n","/etc/wireless/mt7915/l1profile.dat");
    goto LAB_0014f5b0;
  }
LAB_0014f270:
  sVar11 = 1;
  goto LAB_0014f5c4;
code_r0x0014f464:
  bVar9 = true;
LAB_0014f48c:
  os_free_mem(local_78);
  if (bVar9) {
LAB_0014f67c:
    if (1 < DebugLevel) {
      printk("[%d]%s not found, keep default\n",0,&local_74);
    }
  }
  else {
    if (2 < DebugLevel) {
      printk("[%d]%s found by chip\n",0,&local_74);
    }
LAB_0014f4bc:
    os_alloc_mem(0,&local_7c,0x800);
    if (local_7c != 0) {
      sVar4 = 1;
      iVar8 = RTMPGetKeyParameter(&_LANCHOR0,local_7c,0x800,local_80,1);
      if (iVar8 == 0) {
        if (1 < DebugLevel) {
          printk("%s not found!!\n",&_LANCHOR0);
        }
      }
      else {
        if (2 < DebugLevel) {
          printk("Chip=%s\n",local_7c);
        }
        pcVar10 = s_profile_path_0033ae50;
        do {
          sprintf(acStack_46,"%s_%s",&_LANCHOR0,pcVar10);
          iVar8 = RTMPGetKeyParameter(acStack_46,local_7c,0x800,local_80,1);
          if (iVar8 == 0) {
            if (1 < DebugLevel) {
              printk("%s not found\n",pcVar10);
            }
          }
          else {
            if (2 < DebugLevel) {
              printk("%s=%s\n",pcVar10,local_7c);
            }
            if (*(code **)(pcVar10 + 0x24) == (code *)0x0) {
              if (-1 < DebugLevel) {
                printk("unknown handler for %s, ignored!\n",pcVar10);
              }
            }
            else {
              (**(code **)(pcVar10 + 0x24))(param_1,*(undefined4 *)(pcVar10 + 0x20),local_7c);
            }
          }
          pcVar10 = pcVar10 + 0x28;
        } while (pcVar10 != l1profile_default);
        sVar4 = 0;
      }
      os_free_mem(local_7c);
    }
  }
LAB_0014f5b0:
  sVar11 = sVar4;
  if (iVar6 == 0) {
LAB_0014f614:
    local_50 = 0;
    iVar6 = os_file_close(local_60,uStack_5c,uStack_58,uStack_54,0,iVar3);
    sVar11 = sVar4;
    if (iVar6 != 0) {
      if (-1 < DebugLevel) {
        sVar11 = 1;
        printk("Close file \"%s\" failed(errCode=%d)!\n","/etc/wireless/mt7915/l1profile.dat",sVar4)
        ;
        goto LAB_0014f5c4;
      }
      goto LAB_0014f270;
    }
  }
  if (2 < DebugLevel) {
    printk("Close file \"%s\" succeed!\n","/etc/wireless/mt7915/l1profile.dat");
  }
LAB_0014f5c4:
  if (local_80 != (void *)0x0) {
    os_free_mem(local_80);
  }
  return sVar11;
}

