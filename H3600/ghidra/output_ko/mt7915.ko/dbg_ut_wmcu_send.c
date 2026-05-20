// module: mt7915.ko
// function: dbg_ut_wmcu_send @ 0x28e02c
// size: 488 bytes
//

undefined4 dbg_ut_wmcu_send(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined1 *local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  code *local_1c;
  
  uVar2 = param_2[2];
  if ((uint)param_2[2] < (uint)param_2[3]) {
    uVar2 = param_2[3];
  }
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  printk(&_LC7,"FRAMEWORK","dbg_ut_wmcu_send",*param_2,param_2[1]);
  uVar3 = uVar2 + 0x10 & 0xffff;
  printk(&_LC8,"FRAMEWORK","dbg_ut_wmcu_send",param_2[2],param_2[4]);
  uVar4 = param_2[5];
  printk(&_LC9,"FRAMEWORK","dbg_ut_wmcu_send",param_2[3],uVar4);
  os_alloc_mem(param_1,&local_30,uVar3);
  if ((local_30 != (undefined1 *)0x0) && (iVar1 = AndesAllocCmdMsg(param_1,uVar3), iVar1 != 0)) {
    local_1c = (code *)param_2[6];
    local_20 = param_2[5];
    local_28 = CONCAT22((short)param_2[3] + 0x10,(undefined2)local_28);
    local_24 = CONCAT22(local_24._2_2_,10000);
    if (local_1c == (code *)0x0) {
      local_1c = dbg_txcmd_ut_wmcu_resp;
    }
    local_2c = CONCAT13(0xa2,CONCAT12(0xed,(undefined2)local_2c));
    local_28 = CONCAT31(local_28._1_3_,0xf);
    AndesInitCmdMsg(iVar1,local_2c,local_28,local_24,local_20,local_1c);
    *(undefined4 *)(local_30 + 4) = *param_2;
    *(undefined4 *)(local_30 + 8) = param_2[1];
    uVar4 = param_2[2];
    *(short *)(local_30 + 2) = (short)(uVar2 + 0x10);
    *(undefined4 *)(local_30 + 0xc) = uVar4;
    *local_30 = 0;
    os_move_mem(local_30 + 0x10,(void *)param_2[4],param_2[2]);
    AndesAppendCmdMsg(iVar1,local_30,uVar3);
    iVar1 = chip_cmd_tx(param_1,iVar1);
    printk(&_LC10,"FRAMEWORK","dbg_ut_wmcu_send",iVar1);
    if (iVar1 == 0) {
      uVar4 = 0;
    }
    else {
      uVar4 = 4;
    }
    return uVar4;
  }
  printk(&_LC10,"FRAMEWORK","dbg_ut_wmcu_send",3,uVar4);
  return 4;
}

