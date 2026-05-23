// module: mt7915.ko
// function: MtAsicSetBssidByFw @ 0x197fa4
// size: 4 bytes
//

undefined4 MtAsicSetBssidByFw(undefined4 param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  short sVar5;
  uint *puVar6;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  code *pcStack_2c;
  
  sVar5 = 0;
  uStack_44 = 0;
  uStack_40 = 0;
  if ((*(uint *)(param_2 + 0x3c) & 0x8000) == 0) {
    uVar3 = 0xf4;
  }
  else {
    uVar3 = 0x5f0;
  }
  uStack_3c = 0;
  uStack_38 = 0;
  uStack_34 = 0;
  uStack_30 = 0;
  iVar2 = AndesAllocCmdMsg(param_1,uVar3);
  if (iVar2 == 0) {
    uVar3 = 3;
  }
  else {
    uVar4 = 0;
    do {
      uVar1 = uVar4 & 0xff;
      uVar4 = uVar4 + 1;
      if ((*(uint *)(param_2 + 0x3c) & 1 << uVar1) != 0) {
        sVar5 = sVar5 + 1;
      }
    } while (uVar4 != 0x11);
    if (2 < DebugLevel) {
      printk("%s(): OwnMacIdx = %d, Band = %d, BssIndex = %d (%02x:%02x:%02x:%02x:%02x:%02x), TLV Num = %d\n"
             ,"CmdExtBssInfoUpdate",*(undefined1 *)(param_2 + 0xc),*(undefined1 *)(param_2 + 0x106),
             *(undefined1 *)(param_2 + 0xd),*(undefined1 *)(param_2 + 0xe),
             *(undefined1 *)(param_2 + 0xf),*(undefined1 *)(param_2 + 0x10),
             *(undefined1 *)(param_2 + 0x11),*(undefined1 *)(param_2 + 0x12),
             *(undefined1 *)(param_2 + 0x13),sVar5);
    }
    pcStack_2c = CmdExtBssInfoUpdateRsp;
    uStack_38 = CONCAT22(0x10,(undefined2)uStack_38);
    uStack_3c = CONCAT13(0x26,CONCAT12(0xed,(undefined2)uStack_3c));
    uStack_38 = CONCAT31(uStack_38._1_3_,0x27);
    AndesInitCmdMsg(iVar2,uStack_3c,uStack_38,uStack_34,uStack_30,CmdExtBssInfoUpdateRsp);
    uStack_44 = CONCAT22(sVar5,(undefined2)uStack_44);
    puVar6 = &DAT_002a03c8;
    uStack_40 = CONCAT31(uStack_40._1_3_,1);
    uStack_44 = CONCAT31(uStack_44._1_3_,*(undefined1 *)(param_2 + 0xd));
    AndesAppendCmdMsg(iVar2,&uStack_44,8);
    do {
      if ((*puVar6 & *(uint *)(param_2 + 0x3c)) != 0) {
        if ((code *)puVar6[1] == (code *)0x0) {
          if (0 < DebugLevel) {
            printk("%s: BssInfoTag = %d no corresponding function handler.\n","CmdExtBssInfoUpdate",
                   *puVar6);
          }
        }
        else {
          (*(code *)puVar6[1])(param_1,param_2,iVar2);
        }
      }
      puVar6 = puVar6 + 2;
    } while (puVar6 != (uint *)&UNK_002a0450);
    call_fw_cmd_notifieriers(4,param_1,*(undefined4 *)(iVar2 + 0x20));
    uVar3 = AndesSendCmdMsg(param_1,iVar2);
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d)\n","CmdExtBssInfoUpdate",uVar3);
  }
  return uVar3;
}

