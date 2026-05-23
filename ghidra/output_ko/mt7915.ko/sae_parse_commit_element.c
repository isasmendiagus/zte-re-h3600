// module: mt7915.ko
// function: sae_parse_commit_element @ 0x209a1c
// size: 144 bytes
//

undefined4
sae_parse_commit_element(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_parse_commit_element",param_3,DebugLevel,param_4);
  }
  log_time_begin(0,param_1 + 0xc4);
  if (*(int *)(param_1 + 0x98) == 0) {
    uVar1 = 1;
  }
  else {
    uVar1 = (**(code **)(*(int *)(param_1 + 0x98) + 0xc))(param_1,param_2,param_3);
  }
  log_time_end(1,"parse_commit_element_time",3,param_1 + 0xc4);
  return uVar1;
}

