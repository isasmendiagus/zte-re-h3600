// module: mt7915.ko
// function: RtmpMgmtTaskInit @ 0xc4da8
// size: 172 bytes
//

undefined4 RtmpMgmtTaskInit(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  code *pcVar3;
  
  RtmpCmdQInit();
  pcVar3 = mt_ate_ampdu_frame + param_1;
  RtmpOSTaskInit(pcVar3,"RtmpCmdQTask",param_1,param_1 + 0xa78454,param_1 + 0xa78478);
  iVar1 = RtmpOSTaskAttach(pcVar3,hif_cmd_thread,pcVar3);
  if (iVar1 == 1) {
    uVar2 = 1;
    if (-1 < DebugLevel) {
      printk(&_LC13,*(undefined4 *)(param_1 + 4));
    }
  }
  else {
    WscThreadInit(param_1);
    uVar2 = 0;
  }
  return uVar2;
}

