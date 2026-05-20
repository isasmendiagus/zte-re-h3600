// module: mt7915.ko
// function: mt_cmd_set_pls_thres_param @ 0x1b9854
// size: 296 bytes
//

undefined4 mt_cmd_set_pls_thres_param(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  
  iVar1 = AndesAllocCmdMsg(param_1,0x20);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    os_zero_mem(&local_48,0x20);
    uStack_44 = *(undefined4 *)(param_2 + 4);
    uStack_40 = *(undefined4 *)(param_2 + 8);
    uStack_3c = *(undefined4 *)(param_2 + 0xc);
    local_38 = *(undefined4 *)(param_2 + 0x10);
    uStack_34 = *(undefined4 *)(param_2 + 0x14);
    uStack_30 = *(undefined4 *)(param_2 + 0x18);
    uStack_2c = *(undefined4 *)(param_2 + 0x1c);
    local_48 = 3;
    AndesInitCmdMsg(iVar1,0x9ded0000,0xffff0008,0,0,0);
    AndesAppendCmdMsg(iVar1,&local_48,0x20);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","mt_cmd_set_pls_thres_param",uVar2);
  }
  return uVar2;
}

