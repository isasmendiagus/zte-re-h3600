// module: mt7915.ko
// function: CmdExtBssInfoUpdate @ 0x1c70a0
// size: 532 bytes
//

undefined4 CmdExtBssInfoUpdate(undefined4 param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  short sVar5;
  uint *puVar6;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  code *local_2c;
  
  sVar5 = 0;
  local_44 = 0;
  local_40 = 0;
  if ((*(uint *)(param_2 + 0x3c) & 0x8000) == 0) {
    uVar3 = 0xf4;
  }
  else {
    uVar3 = 0x5f0;
  }
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
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
    local_2c = CmdExtBssInfoUpdateRsp;
    local_38 = CONCAT22(0x10,(undefined2)local_38);
    local_3c = CONCAT13(0x26,CONCAT12(0xed,(undefined2)local_3c));
    local_38 = CONCAT31(local_38._1_3_,0x27);
    AndesInitCmdMsg(iVar2,local_3c,local_38,local_34,local_30,CmdExtBssInfoUpdateRsp);
    local_44 = CONCAT22(sVar5,(undefined2)local_44);
    puVar6 = &DAT_002a03c8;
    local_40 = CONCAT31(local_40._1_3_,1);
    local_44 = CONCAT31(local_44._1_3_,*(undefined1 *)(param_2 + 0xd));
    AndesAppendCmdMsg(iVar2,&local_44,8);
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

