// module: mt7915.ko
// function: AsicGetMacVersion @ 0x147c30
// size: 184 bytes
//

undefined4 AsicGetMacVersion(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(int *)(iVar1 + 0x30) == 2) {
    if (DebugLevel < 1) {
      return 0;
    }
    printk("%s(%d): Not support for HIF_MT yet!\n","AsicGetMacVersion",0x5b,DebugLevel,param_4);
    return 0;
  }
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0,"Get_RBIST_IQ_Data_Proc" + param_1 + 8);
  if (DebugLevel < 1) {
    return 1;
  }
  printk("MACVersion[Ver:Rev]=0x%08x : 0x%08x\n",
         *(undefined4 *)("Get_RBIST_IQ_Data_Proc" + param_1 + 8),
         *(undefined4 *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc),DebugLevel,param_4);
  return 1;
}

