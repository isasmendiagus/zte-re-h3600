// module: mt7915.ko
// function: hdev_ctrl_init @ 0xa89e4
// size: 164 bytes
//

undefined4 hdev_ctrl_init(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int local_14;
  
  local_14 = 0;
  os_alloc_mem(0,&local_14,0x4330);
  if (local_14 == 0) {
    if (DebugLevel < 3) {
      uVar1 = 0xffffffff;
    }
    else {
      printk("%s(): Allocate Hardware device Configure  fail!!\n","hdev_ctrl_init");
      uVar1 = 0xffffffff;
    }
  }
  else {
    os_zero_mem(local_14,0x4330);
    *(int *)(local_14 + 0x4328) = param_1;
    *(int *)(param_1 + 0xa797a0) = local_14;
    hif_core_ops_register(local_14,param_2);
    uVar1 = 0;
  }
  return uVar1;
}

