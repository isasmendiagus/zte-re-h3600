// module: mt7915.ko
// function: hif_get_resource_type @ 0xaac60
// size: 80 bytes
//

undefined4 hif_get_resource_type(int param_1)

{
  undefined4 uVar1;
  
  if (*(code **)(param_1 + 0xaac) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000aac74. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(param_1 + 0xaac))(param_1 + 0x9f8);
    return uVar1;
  }
  if (DebugLevel < 0) {
    return 0;
  }
  printk("%s() not support !\n","hif_get_resource_type");
  return 0;
}

