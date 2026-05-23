// module: mt7915.ko
// function: hif_sys_init @ 0xab324
// size: 72 bytes
//

undefined4 hif_sys_init(int param_1)

{
  undefined4 uVar1;
  
  if (*(code **)(param_1 + 0xb18) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000ab330. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(param_1 + 0xb18))();
    return uVar1;
  }
  if (DebugLevel < 0) {
    return 1;
  }
  printk("%s() not support !\n","hif_sys_init");
  return 1;
}

