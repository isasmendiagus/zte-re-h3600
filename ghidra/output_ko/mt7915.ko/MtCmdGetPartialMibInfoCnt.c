// module: mt7915.ko
// function: MtCmdGetPartialMibInfoCnt @ 0x1b8820
// size: 264 bytes
//

undefined4 MtCmdGetPartialMibInfoCnt(undefined4 param_1,undefined1 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined2 local_80 [2];
  undefined1 local_7c;
  
  os_zero_mem(local_80,0x68);
  iVar1 = AndesAllocCmdMsg(param_1,0x68);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    AndesInitCmdMsg(iVar1,0x3ced0000,"fsm/sta_mgmt_cntl.c:%d assert reptfailed\n",0,param_3,
                    MtCmdGetPartialMibInfoCntRsp);
    local_80[0] = 3;
    local_7c = param_2;
    AndesAppendCmdMsg(iVar1,local_80,0x68);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdGetPartialMibInfoCnt",uVar2);
  }
  return uVar2;
}

