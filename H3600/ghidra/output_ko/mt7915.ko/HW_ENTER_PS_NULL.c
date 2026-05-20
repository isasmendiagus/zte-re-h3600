// module: mt7915.ko
// function: HW_ENTER_PS_NULL @ 0xb0c8c
// size: 168 bytes
//

void HW_ENTER_PS_NULL(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_14 [2];
  
  local_14[0] = param_2;
  if (2 < DebugLevel) {
    printk("%s::--->\n","HW_ENTER_PS_NULL");
  }
  iVar1 = FUN_000b0a74(param_1,4,0x20,4,local_14);
  if (iVar1 != 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s::Failed to enqueue cmd\n","HW_ENTER_PS_NULL");
  }
  if (2 < DebugLevel) {
    printk("%s::<---\n","HW_ENTER_PS_NULL");
  }
  return;
}

