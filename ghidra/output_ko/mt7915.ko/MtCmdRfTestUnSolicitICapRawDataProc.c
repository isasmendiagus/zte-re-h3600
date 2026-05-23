// module: mt7915.ko
// function: MtCmdRfTestUnSolicitICapRawDataProc @ 0x1ae09c
// size: 692 bytes
//

undefined4 MtCmdRfTestUnSolicitICapRawDataProc(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 uVar5;
  bool bVar6;
  undefined1 auStack_e0 [76];
  uint local_94;
  undefined4 local_90;
  int *local_88;
  int local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  
  local_84 = param_1 + 0xa70000;
  local_88 = &DebugLevel;
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar5 = *(undefined4 *)(param_1 + 0xa78acc);
  if (2 < DebugLevel) {
    printk("%s----------------->\n","MtCmdRfTestUnSolicitICapRawDataProc");
  }
  iVar4 = 0;
  os_zero_mem(&local_80,0x58);
  *(undefined4 *)(param_1 + 0xa78abc) = 0;
  local_7c = 0x11;
  local_80 = CONCAT31(local_80._1_3_,1);
  __init_waitqueue_head(param_1 + 0xa78ac0,"&x->wait",&_LANCHOR1);
  *(undefined4 *)(param_1 + 0xa78a50) = 1;
  *(undefined4 *)(param_1 + 0xa78a64) = 0;
  *(undefined4 *)(param_1 + 0xa78a68) = 0;
  *(undefined4 *)(param_1 + 0xa78a74) = 0;
  *(undefined4 *)(param_1 + 0xa78a70) = 0;
  *(undefined4 *)(param_1 + 0xa78a6c) = 0;
  os_zero_mem(uVar5,*(int *)(iVar1 + 0x168) << 5);
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7622) {
    bVar6 = *(char *)(iVar1 + 0x164) == '\0';
    if (!bVar6) {
      do {
        puVar3 = (undefined4 *)(*(int *)(iVar1 + 0x160) + iVar4 * 0x1f);
        local_78 = *puVar3;
        local_74 = puVar3[1];
        local_70 = puVar3[2];
        local_6c = puVar3[3];
        *(int *)(param_1 + 0xa78a78) = iVar4;
        iVar4 = iVar4 + 1;
        local_90 = 8;
        local_94 = (uint)bVar6;
        memcpy(auStack_e0,&local_74,0x4c);
        FUN_001abb34(param_1,local_80,local_7c,local_78);
        uVar5 = RTMPMsecsToJiffies(100000);
        iVar2 = wait_for_completion_timeout(param_1 + 0xa78abc,uVar5);
        if (iVar2 == 0) {
          iVar1 = *local_88;
          if (-1 < *local_88) {
            printk(&_LC75);
            iVar1 = DebugLevel;
          }
          uVar5 = 2;
          *(undefined4 *)(local_84 + 0x8a50) = 2;
          goto LAB_001ae1cc;
        }
      } while (iVar4 < (int)(uint)*(byte *)(iVar1 + 0x164));
    }
  }
  else {
    local_94 = 0;
    local_90 = 8;
    memcpy(auStack_e0,&local_74,0x4c);
    FUN_001abb34(param_1,local_80,local_7c,local_78);
    uVar5 = RTMPMsecsToJiffies(100000);
    iVar1 = wait_for_completion_timeout(param_1 + 0xa78abc,uVar5);
    if (iVar1 == 0) {
      iVar1 = *local_88;
      if (-1 < *local_88) {
        printk(&_LC75);
        iVar1 = DebugLevel;
      }
      uVar5 = 2;
      *(undefined4 *)(local_84 + 0x8a50) = 2;
      goto LAB_001ae1cc;
    }
  }
  uVar5 = *(undefined4 *)(param_1 + 0xa78a50);
  iVar1 = *local_88;
LAB_001ae1cc:
  if ((0 < iVar1) &&
     (printk("%s:(Status = %d)\n","MtCmdRfTestUnSolicitICapRawDataProc",uVar5), 2 < *local_88)) {
    printk("%s<-----------------\n","MtCmdRfTestUnSolicitICapRawDataProc");
  }
  return uVar5;
}

