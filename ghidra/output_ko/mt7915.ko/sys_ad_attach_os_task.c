// module: mt7915.ko
// function: sys_ad_attach_os_task @ 0x25ec40
// size: 144 bytes
//

undefined4 sys_ad_attach_os_task(int param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  
  *(undefined1 *)(param_1 + 0x18) = 0;
  if (*(int *)(param_1 + 0x1c) != 0) {
    printk("%s non-null kthread_task %s\n","_sys_ad_attach_os_task",param_1);
    return 0x700;
  }
  uVar1 = kthread_create_on_node(param_2,param_3,0xffffffff,param_1);
  if (uVar1 < 0xfffff001) {
    wake_up_process();
    *(uint *)(param_1 + 0x1c) = uVar1;
    return 0;
  }
  *(uint *)(param_1 + 0x1c) = uVar1;
  printk("%s kthread_run %s err %ld\n","_sys_ad_attach_os_task",param_1,uVar1);
  *(undefined4 *)(param_1 + 0x1c) = 0;
  return 0x700;
}

