// module: mt7915.ko
// function: cmd_txbf_en_dynsnd_intr @ 0x1b3db8
// size: 252 bytes
//

undefined4 cmd_txbf_en_dynsnd_intr(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (-1 < DebugLevel) {
    printk("%s: is_intr_en = %d\n","cmd_txbf_en_dynsnd_intr",param_2);
  }
  iVar1 = AndesAllocCmdMsg(param_1,4);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    AndesInitCmdMsg(iVar1,0x1eed0000,0xffff0008,0,0,0);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (-1 < DebugLevel) {
    printk("%s:(ret = %d)\n","cmd_txbf_en_dynsnd_intr",uVar2);
  }
  return uVar2;
}

