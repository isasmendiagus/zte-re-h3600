// module: mt7915.ko
// function: ShowHeraMuRaInfoProc @ 0x1be1d8
// size: 500 bytes
//

undefined4 ShowHeraMuRaInfoProc(undefined4 param_1,char *param_2)

{
  undefined2 uVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  int iVar6;
  undefined4 uVar7;
  char *local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined2 local_38;
  undefined2 uStack_36;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_3c = 0;
  local_38 = 0;
  uStack_36 = 0;
  local_40 = 3;
  local_44 = param_2;
  pcVar2 = strsep(&local_44,"-");
  if ((((pcVar2 != (char *)0x0) && (pcVar3 = strsep(&local_44,"-"), pcVar3 != (char *)0x0)) &&
      (pcVar4 = strsep(&local_44,"-"), pcVar4 != (char *)0x0)) &&
     (pcVar5 = strsep(&local_44,""), pcVar5 != (char *)0x0)) {
    uVar1 = simple_strtol(pcVar2,0,10);
    local_3c = CONCAT22(local_3c._2_2_,uVar1);
    uVar1 = simple_strtol(pcVar3,0,10);
    local_3c = CONCAT22(uVar1,(undefined2)local_3c);
    uVar1 = simple_strtol(pcVar4,0,10);
    _local_38 = CONCAT22(uStack_36,uVar1);
    uVar1 = simple_strtol(pcVar5,0,10);
    uStack_36 = uVar1;
    if ((3 < DebugLevel) && (printk(&_LC0,"ShowHeraMuRaInfoProc"), 3 < DebugLevel)) {
      printk("MuGroupIdx: %d UserIdx: %d Direction: %d DumpGroup: %d\n",local_3c & 0xffff,
             local_3c._2_2_,local_38,uStack_36);
    }
    iVar6 = AndesAllocCmdMsg(param_1,0xc);
    if (iVar6 != 0) {
      local_34 = CONCAT13(0x87,CONCAT12(0xed,(undefined2)local_34));
      local_30 = CONCAT31(local_30._1_3_,10);
      uVar7 = 1;
      AndesInitCmdMsg(iVar6,local_34,local_30,local_2c,local_28,local_24);
      AndesAppendCmdMsg(iVar6,&local_40,4);
      AndesAppendCmdMsg(iVar6,&local_3c,8);
      chip_cmd_tx(param_1,iVar6);
      goto LAB_001be35c;
    }
  }
  uVar7 = 0;
LAB_001be35c:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d\n","ShowHeraMuRaInfoProc",uVar7);
  }
  return uVar7;
}

