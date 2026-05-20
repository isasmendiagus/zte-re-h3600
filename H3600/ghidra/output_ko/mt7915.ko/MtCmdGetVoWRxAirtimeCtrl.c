// module: mt7915.ko
// function: MtCmdGetVoWRxAirtimeCtrl @ 0x1b6404
// size: 288 bytes
//

undefined4 MtCmdGetVoWRxAirtimeCtrl(undefined4 param_1,void *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_64 [68];
  
  if (3 < DebugLevel) {
    printk("%s:struct size %zu\n","MtCmdGetVoWRxAirtimeCtrl",0x44);
  }
  iVar1 = AndesAllocCmdMsg(param_1,0x44);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    AndesInitCmdMsg(iVar1,0x4aed0000,s_EVT_ID_0x_02x_SEQ__u_LEN__u_FID__0043ffcc + 0x43,0,param_2,
                    MtCmdSetVoWRxAirtimeCtrlRsp);
    memcpy(auStack_64,param_2,0x44);
    AndesAppendCmdMsg(iVar1,auStack_64,0x44);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdGetVoWRxAirtimeCtrl",uVar2);
  }
  return uVar2;
}

