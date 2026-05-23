// module: mt7915.ko
// function: MtAsicSetAid @ 0x199b98
// size: 4 bytes
//

undefined4 MtAsicSetAid(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 uStack_50;
  undefined1 uStack_4f;
  undefined2 uStack_4e;
  undefined1 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  code *pcStack_24;
  
  uStack_48 = 0;
  uStack_44 = 0;
  uStack_40 = 0;
  uStack_3c = 0;
  if (2 < DebugLevel) {
    printk("%s: Aid = %d\n","CmdETxBfAidSetting",param_2);
  }
  iVar1 = AndesAllocCmdMsg(param_1,8);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    uStack_48 = CONCAT13(0x1e,CONCAT12(0xed,(undefined2)uStack_48));
    uStack_44 = CONCAT31(uStack_44._1_3_,8);
    uStack_44 = CONCAT22(0xffff,(undefined2)uStack_44);
    uStack_4e = (undefined2)param_2;
    uStack_50 = 0xc;
    uStack_4f = 0;
    uStack_34 = uStack_48;
    uStack_30 = uStack_44;
    uStack_2c = uStack_40;
    uStack_28 = uStack_3c;
    pcStack_24 = EventExtCmdResult;
    uStack_4c = 0;
    AndesInitCmdMsg(iVar1,uStack_48,uStack_44,uStack_40,uStack_3c,EventExtCmdResult);
    AndesAppendCmdMsg(iVar1,&uStack_50,8);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdETxBfAidSetting",uVar2);
  }
  return uVar2;
}

