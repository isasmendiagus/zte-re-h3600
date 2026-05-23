// module: mt7915.ko
// function: SetMdvtModuleParameterProc @ 0x1d7850
// size: 732 bytes
//

undefined4 SetMdvtModuleParameterProc(int param_1,char *param_2)

{
  char *pcVar1;
  int iVar2;
  uint uVar3;
  char *__s2;
  int unaff_r6;
  int iVar4;
  uint uVar5;
  uint local_58;
  char *local_4c;
  undefined2 local_46;
  undefined2 local_44;
  undefined2 local_42;
  undefined2 local_40;
  undefined2 local_3e;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  if (param_1 != 0) {
    unaff_r6 = 0xa7c23e;
  }
  local_46 = 0;
  local_44 = 0;
  local_42 = 0;
  local_40 = 0;
  local_3e = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  if (param_1 != 0) {
    iVar4 = param_1 + unaff_r6;
  }
  else {
    iVar4 = 0;
  }
  local_4c = param_2;
  if (((param_2 == (char *)0x0) || (pcVar1 = strsep(&local_4c,"-"), pcVar1 == (char *)0x0)) ||
     (iVar2 = strcmp(pcVar1,"show"), iVar2 == 0)) {
LAB_001d78e8:
    if (DebugLevel < 1) goto LAB_001d78fc;
  }
  else {
    iVar2 = strcmp(pcVar1,"disable");
    uVar3 = u4MdvtModuleUpdateTableSize;
    if (iVar2 == 0) {
      mdvt_disable(param_1);
      return 1;
    }
    if (u4MdvtModuleUpdateTableSize != 0) {
      local_58 = 0;
      do {
        __s2 = *(char **)(arMdvtModuleUpdateTable + local_58 * 8 + 4);
        iVar2 = strcmp(pcVar1,__s2);
        uVar5 = local_58 + 1 & 0xff;
        if (iVar2 == 0) {
          if ((iVar4 != 0) && (*(char *)(iVar4 + 1) == '\0')) {
            mdvt_enable(param_1);
          }
          iVar4 = AndesAllocCmdMsg(param_1,10);
          if (iVar4 == 0) {
            return 0;
          }
          local_3c = CONCAT13(0xaf,CONCAT12(0xed,(undefined2)local_3c));
          local_38 = CONCAT31(local_38._1_3_,10);
          AndesInitCmdMsg(iVar4,local_3c,local_38,local_34,local_30,local_2c);
          local_46 = CONCAT11(local_46._1_1_,1);
          local_44 = (undefined2)*(undefined4 *)(arMdvtModuleUpdateTable + local_58 * 8);
          pcVar1 = strsep(&local_4c,"-");
          if (pcVar1 != (char *)0x0) {
            local_42 = os_str_tol(pcVar1,0,10);
          }
          AndesAppendCmdMsg(iVar4,&local_46,10);
          if (0 < DebugLevel) {
            printk("%s:Module %s Module ID = %d Test Case Idx = %d\n","SetMdvtModuleParameterProc",
                   __s2,local_44,local_42);
          }
          AndesSendCmdMsg(param_1,iVar4);
          uVar3 = u4MdvtModuleUpdateTableSize;
          break;
        }
        local_58 = uVar5;
      } while (uVar5 < uVar3);
      if (uVar3 != local_58) {
        return 1;
      }
      goto LAB_001d78e8;
    }
    if (DebugLevel < 1) {
      return 1;
    }
  }
  printk("iwpriv ra0 set mdvt=(module)-(value)\n");
LAB_001d78fc:
  if (u4MdvtModuleUpdateTableSize != 0) {
    uVar3 = 0;
    do {
      if (0 < DebugLevel) {
        printk("Module Name %s\n",*(undefined4 *)(arMdvtModuleUpdateTable + uVar3 * 8 + 4));
      }
      uVar3 = uVar3 + 1 & 0xff;
    } while (uVar3 < u4MdvtModuleUpdateTableSize);
  }
  return 1;
}

