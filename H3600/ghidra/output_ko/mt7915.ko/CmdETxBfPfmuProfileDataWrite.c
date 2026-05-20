// module: mt7915.ko
// function: CmdETxBfPfmuProfileDataWrite @ 0x1b2714
// size: 656 bytes
//

undefined4
CmdETxBfPfmuProfileDataWrite(int *param_1,undefined4 param_2,undefined4 param_3,void *param_4)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_40;
  undefined1 local_3f;
  undefined2 local_3e;
  undefined1 local_3c;
  undefined1 local_3b;
  undefined1 local_3a;
  undefined1 local_39;
  undefined1 local_38;
  undefined1 local_37;
  undefined1 local_36;
  undefined1 local_35;
  undefined1 local_34;
  undefined1 local_33;
  undefined1 local_32;
  undefined1 local_31;
  undefined1 local_30;
  undefined1 local_2f;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined1 local_29;
  
  get_wdev_by_ioctl_idx_and_iftype
            (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  uVar1 = HcGetBandByWdev();
  iVar4 = param_1[0x29deee];
  if (param_4 == (void *)0x0) {
    uVar3 = 2;
  }
  else {
    iVar2 = AndesAllocCmdMsg(param_1,0x18);
    if (iVar2 == 0) {
      uVar3 = 3;
    }
    else {
      os_zero_mem(&local_40,0x18);
      local_3f = (undefined1)param_2;
      local_3e = (undefined2)param_3;
      local_40 = 8;
      if (((param_1[0x28eb05] & 1U) != 0) ||
         ((param_1[0x29deed] == 1 && ((*(uint *)(param_1[0x29deee] + 0x4e0) & 1) != 0)))) {
        uVar1 = (uint)*(byte *)(iVar4 + 0x4cc);
      }
      local_29 = (undefined1)uVar1;
      if (2 < DebugLevel) {
        printk("%s: PFMU ID = %d, Subcarrier:%d, Band:%d\n","CmdETxBfPfmuProfileDataWrite",param_2,
               param_3,uVar1);
      }
      os_move_mem(&local_3c,param_4,0x10);
      if ((((2 < DebugLevel) &&
           (printk("Buf[0~3]= %x:%x:%x:%x\n",local_3c,local_3b,local_3a,local_39), 2 < DebugLevel))
          && (printk("Buf[4~7]= %x:%x:%x:%x\n",local_38,local_37,local_36,local_35), 2 < DebugLevel)
          ) && (printk("Buf[8~11]= %x:%x:%x:%x\n",local_34,local_33,local_32,local_31),
               2 < DebugLevel)) {
        printk("Buf[12~15]= %x:%x:%x:%x\n",local_30,local_2f,local_2e,local_2d);
      }
      AndesInitCmdMsg(iVar2,0x1eed0000,0xffff0008,0,0,EventExtCmdResult);
      AndesAppendCmdMsg(iVar2,&local_40,0x18);
      uVar3 = chip_cmd_tx(param_1,iVar2);
    }
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdETxBfPfmuProfileDataWrite",uVar3);
  }
  return uVar3;
}

