// module: mt7915.ko
// function: Get_System_Wireless_Info @ 0xebb0c
// size: 192 bytes
//

undefined4
Get_System_Wireless_Info(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = simple_strtol(param_2,0,10,param_4,param_4);
  if (iVar1 != 0) {
    if (iVar1 == 1) {
      uVar2 = *(undefined4 *)(param_1 + 0xa78a80);
      if (2 < DebugLevel) {
        printk("%s : CaptureNode = 0x%08x\n","Get_System_CapNode_Info",uVar2);
      }
      Get_System_Bw_Info(param_1,uVar2);
    }
    return 1;
  }
  uVar2 = *(undefined4 *)(param_1 + 0xa78a80);
  if (2 < DebugLevel) {
    printk("%s : CaptureNode = 0x%08x\n","Get_System_CapNode_Info",uVar2);
  }
  Get_System_CenFreq_Info(param_1,uVar2);
  return 1;
}

