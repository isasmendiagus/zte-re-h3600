// module: mt7915.ko
// function: Get_System_CapNode_Info @ 0xeb6d4
// size: 68 bytes
//

undefined4 Get_System_CapNode_Info(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)(param_1 + 0xa78a80);
  if (2 < DebugLevel) {
    printk("%s : CaptureNode = 0x%08x\n","Get_System_CapNode_Info",uVar1);
  }
  return uVar1;
}

