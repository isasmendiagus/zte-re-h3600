// module: mt7915.ko
// function: muru_tam_arb_op_mode @ 0x23f6cc
// size: 88 bytes
//

void muru_tam_arb_op_mode(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  bool bVar2;
  
  if (*(uint *)(param_1 + 0x7959ac) == 0) {
    bVar2 = true;
  }
  else {
    iVar1 = wifi_test_muru_set_arb_op_mode(param_1,*(uint *)(param_1 + 0x7959ac) & 0xff,param_3);
    bVar2 = iVar1 != 0;
  }
  if (DebugLevel < 4) {
    return;
  }
  printk("%s:(Ret = %d_\n","muru_tam_arb_op_mode",bVar2,param_4);
  return;
}

