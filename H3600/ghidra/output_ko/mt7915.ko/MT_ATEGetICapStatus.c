// module: mt7915.ko
// function: MT_ATEGetICapStatus @ 0x27dd58
// size: 276 bytes
//

undefined4 MT_ATEGetICapStatus(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (2 < DebugLevel) {
    printk(&_LC65,"MT_ATEGetICapStatus");
  }
  if (*(code **)(iVar1 + 0x18c) == (code *)0x0) {
    uVar2 = 0;
    if (-1 < DebugLevel) {
      printk("%s : The function is not hooked !!\n","MT_ATEGetICapStatus");
    }
  }
  else {
    uVar2 = (**(code **)(iVar1 + 0x18c))(param_1);
    if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7615) {
      wait_for_completion_timeout(param_1 + 0xa3ba38,*(undefined4 *)(param_1 + 0xa3ba48));
      if (2 < DebugLevel) {
        printk("%s, StartAddr1:%02x StartAddr2:%02x StartAddr3:%02x EndAddr:%02x StopAddr:%02x Wrap:%02x\n"
               ,"MT_ATEGetICapStatus",*(undefined4 *)(param_1 + 0xa3ae1d),
               *(undefined4 *)(param_1 + 0xa3ae21),*(undefined4 *)(param_1 + 0xa3ae25),
               *(undefined4 *)(param_1 + 0xa3ae29),*(undefined4 *)(param_1 + 0xa3ae2d),
               *(undefined4 *)(param_1 + 0xa3ae31));
      }
    }
  }
  return uVar2;
}

