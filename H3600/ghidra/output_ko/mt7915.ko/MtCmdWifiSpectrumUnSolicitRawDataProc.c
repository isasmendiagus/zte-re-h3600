// module: mt7915.ko
// function: MtCmdWifiSpectrumUnSolicitRawDataProc @ 0x1ad784
// size: 1008 bytes
//

undefined4 MtCmdWifiSpectrumUnSolicitRawDataProc(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined1 auStack_148 [120];
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  int local_b4;
  undefined4 local_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined1 auStack_a0 [72];
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  
  local_b4 = param_1 + 0xa70000;
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (2 < DebugLevel) {
    printk("%s----------------->\n","MtCmdWifiSpectrumUnSolicitRawDataProc");
  }
  iVar1 = local_b4;
  os_zero_mem(&local_ac,0x84);
  iVar7 = 0;
  *(undefined4 *)(iVar1 + 0x8aac) = 0;
  local_ac = 2;
  __init_waitqueue_head(param_1 + 0xa78ab0,"&x->wait",&_LANCHOR1);
  *(undefined4 *)(iVar1 + 0x8a4c) = 2;
  *(undefined4 *)(iVar1 + 0x8a58) = 0;
  uVar3 = RtmpOSFileOpen(*(undefined4 *)(iVar1 + 0x8aa0),0x41,0);
  *(uint *)(iVar1 + 0x8a94) = uVar3;
  if ((uVar3 == 0) || (0xfffff000 < uVar3)) {
    if (DebugLevel < 0) goto LAB_001ad980;
    printk("--> Error opening %s\n",*(undefined4 *)(iVar1 + 0x8aa0));
  }
  else {
    uVar3 = RtmpOSFileOpen(*(undefined4 *)(iVar1 + 0x8aa4),0x41,0);
    *(uint *)(iVar1 + 0x8a98) = uVar3;
    if ((uVar3 == 0) || (0xfffff000 < uVar3)) {
      if (-1 < DebugLevel) {
        printk("--> Error opening %s\n",*(undefined4 *)(iVar1 + 0x8aa4));
      }
    }
    else {
      uVar3 = RtmpOSFileOpen(*(undefined4 *)(iVar1 + 0x8aa8),0x41,0);
      *(uint *)(iVar1 + 0x8a9c) = uVar3;
      if ((uVar3 == 0) || (0xfffff000 < uVar3)) {
        if (-1 < DebugLevel) {
          printk("--> Error opening %s\n",*(undefined4 *)(iVar1 + 0x8aa8));
        }
      }
      else if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7622) {
        if (*(char *)(iVar2 + 400) != '\0') {
          do {
            puVar6 = (undefined4 *)(*(int *)(iVar2 + 0x18c) + iVar7 * 0x1f);
            local_58 = *puVar6;
            local_54 = puVar6[1];
            local_50 = puVar6[2];
            local_4c = puVar6[3];
            *(int *)(iVar1 + 0x8a5c) = iVar7;
            iVar7 = iVar7 + 1;
            local_d0 = 8;
            local_cc = 0;
            local_c8 = 0;
            local_c4 = 0;
            local_c0 = 0;
            memcpy(auStack_148,auStack_a0,0x78);
            FUN_001abc64(param_1,local_ac,uStack_a8,uStack_a4);
            uVar4 = RTMPMsecsToJiffies(100000);
            iVar5 = wait_for_completion_timeout(param_1 + 0xa78aac,uVar4);
            if (iVar5 == 0) goto LAB_001ad940;
          } while (iVar7 < (int)(uint)*(byte *)(iVar2 + 400));
        }
      }
      else {
        local_cc = 0;
        local_d0 = 8;
        local_c8 = 0;
        local_c4 = 0;
        local_c0 = 0;
        memcpy(auStack_148,auStack_a0,0x78);
        FUN_001abc64(param_1,local_ac,uStack_a8,uStack_a4);
        uVar4 = RTMPMsecsToJiffies(100000);
        iVar2 = wait_for_completion_timeout(param_1 + 0xa78aac,uVar4);
        if (iVar2 == 0) {
LAB_001ad940:
          if (-1 < DebugLevel) {
            printk(&_LC71);
          }
        }
      }
    }
  }
  if ((*(uint *)(iVar1 + 0x8a94) != 0) && (*(uint *)(iVar1 + 0x8a94) < 0xfffff001)) {
    iVar2 = RtmpOSFileClose();
    if ((iVar2 != 0) && (-1 < DebugLevel)) {
      printk("--> Error %d closing %s\n",-iVar2,*(undefined4 *)(iVar1 + 0x8aa0));
    }
    *(undefined4 *)(iVar1 + 0x8a94) = 0;
  }
LAB_001ad980:
  if ((*(uint *)(iVar1 + 0x8a98) != 0) && (*(uint *)(iVar1 + 0x8a98) < 0xfffff001)) {
    iVar2 = RtmpOSFileClose();
    if ((iVar2 != 0) && (-1 < DebugLevel)) {
      printk("--> Error %d closing %s\n",-iVar2,*(undefined4 *)(iVar1 + 0x8aa4));
    }
    *(undefined4 *)(iVar1 + 0x8a98) = 0;
  }
  iVar2 = DebugLevel;
  if ((*(uint *)(iVar1 + 0x8a9c) != 0) && (*(uint *)(iVar1 + 0x8a9c) < 0xfffff001)) {
    iVar2 = RtmpOSFileClose();
    if ((iVar2 != 0) && (-1 < DebugLevel)) {
      printk("--> Error %d closing %s\n",-iVar2,*(undefined4 *)(iVar1 + 0x8aa8));
    }
    iVar2 = DebugLevel;
    *(undefined4 *)(iVar1 + 0x8a9c) = 0;
  }
  uVar4 = *(undefined4 *)(local_b4 + 0x8a4c);
  if ((0 < iVar2) &&
     (printk("%s:(Status = %d)\n","MtCmdWifiSpectrumUnSolicitRawDataProc",uVar4), 2 < DebugLevel)) {
    printk("%s<-----------------\n","MtCmdWifiSpectrumUnSolicitRawDataProc");
  }
  return uVar4;
}

