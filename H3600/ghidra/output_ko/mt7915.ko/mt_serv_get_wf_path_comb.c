// module: mt7915.ko
// function: mt_serv_get_wf_path_comb @ 0x2529f4
// size: 80 bytes
//

int mt_serv_get_wf_path_comb(undefined4 *param_1)

{
  int iVar1;
  undefined4 extraout_r3;
  undefined4 in_stack_00000000;
  
  iVar1 = (**(code **)(param_1[0x7c4] + 0x154))(*param_1);
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_get_wf_path_comb",iVar1,extraout_r3,in_stack_00000000);
  }
  return iVar1;
}

