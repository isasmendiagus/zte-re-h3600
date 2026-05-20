// module: mt7915.ko
// function: CmdExtStaRecUpdate @ 0x1c6884
// size: 620 bytes
//

int CmdExtStaRecUpdate(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4,
                      uint param_5)

{
  int iVar1;
  int iVar2;
  uint *puVar3;
  uint *puVar4;
  char cVar5;
  uint *puVar6;
  short sVar7;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  uint local_44;
  undefined4 local_40;
  code *local_3c;
  uint local_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  cVar5 = '\x03';
  local_54 = 0;
  local_50 = 0;
  local_48 = 0;
  local_44 = 0;
  local_c = param_2;
  uStack_8 = param_3;
  uStack_4 = param_4;
  while( true ) {
    puVar6 = &DAT_002a026c;
    iVar2 = 8;
    puVar3 = puVar6;
    do {
      puVar4 = puVar3 + 3;
      if ((param_5 & 1 << (*puVar3 & 0xff)) != 0) {
        iVar2 = iVar2 + puVar3[1];
      }
      puVar3 = puVar4;
    } while (puVar4 != (uint *)"CmdExtStaRecUpdate");
    iVar2 = AndesAllocCmdMsg(param_1,iVar2);
    if (iVar2 == 0) break;
    sVar7 = 0;
    local_40 = 0;
    local_3c = CmdExtStaRecUpdateRsp;
    local_44 = local_44 & 0xffff0000;
    local_4c = 0x25ed0000;
    local_48 = CONCAT31(local_48._1_3_,0x27);
    local_48 = CONCAT22(0x10,(undefined2)local_48);
    AndesInitCmdMsg(iVar2,0x25ed0000,local_48,local_44,0,CmdExtStaRecUpdateRsp);
    local_54 = CONCAT31(CONCAT21(local_54._2_2_,(char)(local_c >> 0x10)),(undefined1)local_c);
    local_50 = CONCAT22(CONCAT11(local_50._3_1_,(byte)(((local_c >> 0x10) << 0x16) >> 0x1e)),
                        CONCAT11(uStack_8._1_1_,(undefined1)local_50));
    do {
      if ((param_5 & 1 << (*puVar6 & 0xff)) != 0) {
        if ((code *)puVar6[2] == (code *)0x0) {
          if (3 < DebugLevel) {
            printk("%s: StaRecTag = %d no corresponding function handler.\n","CmdExtStaRecUpdate",
                   *puVar6);
          }
        }
        else {
          iVar1 = (*(code *)puVar6[2])(param_1,iVar2,&local_c);
          if (iVar1 == 0) {
            sVar7 = sVar7 + 1;
          }
        }
      }
      puVar6 = puVar6 + 3;
    } while (puVar6 != (uint *)"CmdExtStaRecUpdate");
    if (3 < DebugLevel) {
      printk("%s: u2TLVNumber(%d)\n","CmdExtStaRecUpdate",sVar7);
    }
    local_54 = CONCAT22(sVar7,(undefined2)local_54);
    local_50 = CONCAT31(local_50._1_3_,1);
    AndesAppendHeadCmdMsg(iVar2,&local_54,8);
    call_fw_cmd_notifieriers(5,param_1,*(undefined4 *)(iVar2 + 0x20));
    iVar2 = AndesSendCmdMsg(param_1,iVar2);
    do {
      if (cVar5 == '\0' || iVar2 == 0) goto LAB_001c6a80;
      if (1 < DebugLevel) {
        printk("%s:(FW Ret = 0x%x retry=%d)\n","CmdExtStaRecUpdate",iVar2,cVar5);
      }
      iVar2 = FUN_001c2be0(param_1,&local_c);
      cVar5 = cVar5 + -1;
    } while (iVar2 != 0);
  }
  iVar2 = 3;
LAB_001c6a80:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d)\n","CmdExtStaRecUpdate",iVar2);
  }
  return iVar2;
}

