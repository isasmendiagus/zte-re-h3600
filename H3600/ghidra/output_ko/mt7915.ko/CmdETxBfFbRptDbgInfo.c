// module: mt7915.ko
// function: CmdETxBfFbRptDbgInfo @ 0x1b324c
// size: 428 bytes
//

undefined4 CmdETxBfFbRptDbgInfo(int *param_1,undefined1 *param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  uVar4 = 0;
  uVar5 = 0;
  uVar6 = 0;
  get_wdev_by_ioctl_idx_and_iftype
            (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  uVar1 = HcGetBandByWdev();
  iVar3 = param_1[0x29deee];
  iVar2 = AndesAllocCmdMsg(param_1,0x10);
  if (iVar2 == 0) {
    uVar4 = 3;
  }
  else {
    *param_2 = 0x1f;
    if (((param_1[0x28eb05] & 1U) != 0) ||
       ((param_1[0x29deed] == 1 && ((*(uint *)(param_1[0x29deee] + 0x4e0) & 1) != 0)))) {
      uVar1 = (uint)*(byte *)(iVar3 + 0x4cc);
    }
    param_2[4] = (char)uVar1;
    if (2 < DebugLevel) {
      printk("%s: Action:%u, BandIdx:%u, PollPFMUIntrStatTimeOut:%u, FbRptDeQInterval:%u, WlanIdx:%u, PFMUUpdateEn:%u\n"
             ,"CmdETxBfFbRptDbgInfo",param_2[1],uVar1,param_2[5],param_2[6],
             *(undefined2 *)(param_2 + 2),param_2[7],uVar4,uVar5,uVar6);
    }
    AndesInitCmdMsg(iVar2,CONCAT13(0x1e,CONCAT12(0xed,(short)uVar4)),
                    CONCAT22(0xffff,(short)CONCAT31((int3)((uint)uVar5 >> 8),8)),500,0,0);
    AndesAppendCmdMsg(iVar2,param_2,0x10);
    uVar4 = chip_cmd_tx(param_1,iVar2);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdETxBfFbRptDbgInfo",uVar4);
  }
  return uVar4;
}

