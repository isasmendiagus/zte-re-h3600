// module: mt7915.ko
// function: MtCmdRfTestSolicitICapRawDataProc @ 0x1ae354
// size: 592 bytes
//

undefined4
MtCmdRfTestSolicitICapRawDataProc
          (int param_1,int param_2,int *param_3,undefined4 param_4,undefined4 param_5)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 auStack_d8 [76];
  int local_8c;
  undefined4 local_88;
  int local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 uStack_70;
  undefined1 auStack_6c [12];
  undefined4 local_60;
  undefined4 local_5c;
  
  local_7c = 0;
  if (2 < DebugLevel) {
    printk("%s----------------->\n","MtCmdRfTestSolicitICapRawDataProc");
  }
  iVar1 = os_alloc_mem(param_1,&local_7c,0x430);
  if (iVar1 == 0) {
    os_zero_mem(local_7c,0x430);
    os_zero_mem(&local_78,0x58);
    local_74 = 0x11;
    local_78 = CONCAT31(local_78._1_3_,1);
    local_60 = param_5;
    local_8c = local_7c;
    local_88 = 0x430;
    local_5c = param_4;
    memcpy(auStack_d8,auStack_6c,0x4c);
    uVar4 = FUN_001abb34(param_1,local_78,local_74,uStack_70);
    if (*(int *)(local_7c + 4) != *(int *)(param_1 + 0xa78a64)) {
      if (-1 < DebugLevel) {
        printk(&_LC77,"MtCmdRfTestSolicitICapRawDataProc");
      }
      goto LAB_001ae3b4;
    }
    iVar1 = *(int *)(local_7c + 0xc);
    *param_3 = iVar1;
    if (0 < iVar1) {
      puVar2 = (undefined4 *)(param_2 + -4);
      iVar1 = 0;
      do {
        iVar3 = iVar1 + 0xc;
        iVar1 = iVar1 + 1;
        puVar2 = puVar2 + 1;
        *puVar2 = *(undefined4 *)(local_7c + iVar3 * 4);
      } while (iVar1 < *param_3);
    }
    if (*(int *)(local_7c + 0xc) == 0) {
      if ((*(int *)(local_7c + 4) == *(int *)(param_1 + 0xa78a64)) && (0 < DebugLevel)) {
        printk(&_LC78,"MtCmdRfTestSolicitICapRawDataProc");
        goto LAB_001ae3b4;
      }
      if (local_7c == 0) goto LAB_001ae3e0;
      goto LAB_001ae458;
    }
    if (local_7c == 0) goto LAB_001ae3e0;
LAB_001ae3cc:
    *(int *)(param_1 + 0xa78a64) = *(int *)(param_1 + 0xa78a64) + 1;
  }
  else {
    if (DebugLevel < 0) {
      uVar4 = 0;
    }
    else {
      uVar4 = 0;
      printk("%s : Not enough memory for dynamic allocating !!\n",
             "MtCmdRfTestSolicitICapRawDataProc");
    }
LAB_001ae3b4:
    if (local_7c == 0) goto LAB_001ae3e0;
    if (*(int *)(local_7c + 0xc) != 0) goto LAB_001ae3cc;
LAB_001ae458:
    *(undefined4 *)(param_1 + 0xa78a64) = 0;
  }
  os_free_mem();
LAB_001ae3e0:
  if ((2 < DebugLevel) &&
     (printk("%s:(Status = %d)\n","MtCmdRfTestSolicitICapRawDataProc",uVar4), 2 < DebugLevel)) {
    printk("%s<-----------------\n","MtCmdRfTestSolicitICapRawDataProc");
  }
  return uVar4;
}

