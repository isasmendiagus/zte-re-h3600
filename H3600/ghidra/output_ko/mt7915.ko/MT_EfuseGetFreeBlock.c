// module: mt7915.ko
// function: MT_EfuseGetFreeBlock @ 0x27e048
// size: 4 bytes
//

undefined4 MT_EfuseGetFreeBlock(int param_1,undefined1 *param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 uStack_4c;
  undefined1 uStack_4b;
  undefined1 uStack_4a;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  code *pcStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  code *pcStack_24;
  
  uStack_48 = 0;
  uStack_44 = 0;
  uStack_40 = 0;
  pcStack_38 = (code *)0x0;
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7663 ||
      (*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) {
    cVar1 = param_2[1];
    iVar2 = AndesAllocCmdMsg(param_1,4);
    if (iVar2 == 0) {
LAB_001acd5c:
      uVar3 = 3;
      goto LAB_001accbc;
    }
    if (cVar1 == '\0') goto LAB_001acce0;
    if (cVar1 == '\x01') {
      uStack_48._0_3_ = CONCAT12(0xed,(undefined2)uStack_48);
      uStack_48 = CONCAT13(0x4f,(undefined3)uStack_48);
      uStack_44 = CONCAT31(uStack_44._1_3_,7);
      uStack_44 = CONCAT22(4,(undefined2)uStack_44);
      uStack_34 = uStack_48;
      uStack_30 = uStack_44;
      uStack_2c = uStack_40;
      pcStack_24 = CmdEfuseFreeBlockCountCb;
      uStack_3c = param_3;
      uStack_28 = param_3;
      AndesInitCmdMsg(iVar2,uStack_48,uStack_44,uStack_40,param_3,CmdEfuseFreeBlockCountCb);
      os_zero_mem(&uStack_4c,4);
      uStack_4b = param_2[1];
      uStack_4a = param_2[2];
      if (0 < DebugLevel) {
        printk("%s:\tVersion = %x  DieIndex:%d\n","MtCmdEfuseFreeBlockCount");
      }
    }
    else {
      uStack_44._1_3_ = uStack_44._1_3_ & 0xff;
      uStack_3c = 0;
      uStack_48._0_3_ = CONCAT12(0xed,(undefined2)uStack_48);
      uStack_48 = CONCAT13(0x4f,(undefined3)uStack_48);
      uStack_44 = CONCAT31(uStack_44._1_3_,7);
      uStack_34 = uStack_48;
      uStack_30 = uStack_44;
      uStack_2c = uStack_40;
      uStack_28 = 0;
      pcStack_24 = (code *)0x0;
      AndesInitCmdMsg(iVar2,uStack_48,uStack_44,uStack_40,0,0);
      os_zero_mem(&uStack_4c,4);
    }
  }
  else {
    iVar2 = AndesAllocCmdMsg(param_1,4);
    if (iVar2 == 0) goto LAB_001acd5c;
LAB_001acce0:
    uStack_48._0_3_ = CONCAT12(0xed,(undefined2)uStack_48);
    uStack_48 = CONCAT13(0x4f,(undefined3)uStack_48);
    uStack_44 = CONCAT31(uStack_44._1_3_,7);
    uStack_44 = CONCAT22(8,(undefined2)uStack_44);
    uStack_34 = uStack_48;
    uStack_30 = uStack_44;
    uStack_2c = uStack_40;
    pcStack_24 = pcStack_38;
    uStack_3c = param_3;
    uStack_28 = param_3;
    AndesInitCmdMsg(iVar2,uStack_48,uStack_44,uStack_40,param_3,pcStack_38);
    os_zero_mem(&uStack_4c,4);
    uStack_4c = *param_2;
  }
  AndesAppendCmdMsg(iVar2,&uStack_4c,4);
  uVar3 = chip_cmd_tx(param_1,iVar2);
LAB_001accbc:
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdEfuseFreeBlockCount",uVar3);
  }
  return uVar3;
}

