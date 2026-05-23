// module: mt7915.ko
// function: MtCmdGetWifiInterruptCnt @ 0x1b8a74
// size: 284 bytes
//

undefined4
MtCmdGetWifiInterruptCnt
          (undefined4 param_1,undefined1 param_2,short param_3,undefined4 param_4,undefined4 param_5
          )

{
  int iVar1;
  undefined4 uVar2;
  int local_ac;
  undefined2 local_88 [2];
  undefined1 local_84;
  undefined1 local_83;
  undefined4 local_80;
  
  os_zero_mem(local_88,0x68);
  iVar1 = AndesAllocCmdMsg(param_1,0x68);
  if (iVar1 != 0) {
    local_ac = (uint)(ushort)((param_3 + 2) * 4) << 0x10;
    local_ac = CONCAT31(local_ac._1_3_,7);
    AndesInitCmdMsg(iVar1,0x3ced0000,local_ac,0,param_5,MtCmdGetWifiInterruptCntRsp);
    local_88[0] = 5;
    local_83 = (undefined1)param_3;
    local_84 = param_2;
    local_80 = param_4;
    AndesAppendCmdMsg(iVar1,local_88,0x68);
    uVar2 = chip_cmd_tx(param_1,iVar1);
    return uVar2;
  }
  if (-1 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdGetWifiInterruptCnt",3);
  }
  return 3;
}

