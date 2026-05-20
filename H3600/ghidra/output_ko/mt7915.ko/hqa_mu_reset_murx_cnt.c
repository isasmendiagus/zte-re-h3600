// module: mt7915.ko
// function: hqa_mu_reset_murx_cnt @ 0x93d48
// size: 196 bytes
//

undefined4 hqa_mu_reset_murx_cnt(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  if (param_2 != 0) {
    iVar2 = simple_strtoul(param_2,0,10);
    if (0 < DebugLevel) {
      printk("%s: Reset:%u\n","hqa_mu_reset_murx_cnt",iVar2);
    }
    iVar1 = DebugLevel;
    if (iVar2 != 0) {
      *(undefined4 *)(param_1 + 0xa789d8) = 0;
      if (0 < iVar1) {
        printk("%s:Reset MURX pkt cnt success!\n","hqa_mu_reset_murx_cnt");
      }
    }
    return 1;
  }
  if (DebugLevel < 0) {
    return 0;
  }
  printk("%s: Argument is NULL\n","hqa_mu_reset_murx_cnt");
  return 0;
}

