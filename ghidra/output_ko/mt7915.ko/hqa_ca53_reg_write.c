// module: mt7915.ko
// function: hqa_ca53_reg_write @ 0x24c5c8
// size: 208 bytes
//

undefined4 hqa_ca53_reg_write(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_20;
  undefined1 auStack_1c [8];
  
  local_20 = param_2 + 0xc;
  FUN_002474f4(1,4,&local_20,param_1 + 0x1f14);
  FUN_002474f4(1,4,&local_20,auStack_1c);
  iVar1 = sys_ad_alloc_mem(param_1 + 0x1f1c,4);
  if (iVar1 == 0) {
    sys_ad_move_mem(*(void **)(param_1 + 0x1f1c),auStack_1c,4);
    uVar2 = mt_serv_reg_eprm_operation(param_1,6);
    FUN_00246b90(param_2,2,uVar2);
    sys_ad_free_mem(*(undefined4 *)(param_1 + 0x1f1c));
  }
  else {
    printk("%s: allocate register memory fail\n","hqa_ca53_reg_write");
    FUN_00246b90(param_2,2,0x101);
    uVar2 = 0x101;
  }
  return uVar2;
}

