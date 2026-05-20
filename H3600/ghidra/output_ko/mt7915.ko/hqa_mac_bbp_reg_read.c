// module: mt7915.ko
// function: hqa_mac_bbp_reg_read @ 0x24b428
// size: 196 bytes
//

undefined4 hqa_mac_bbp_reg_read(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int local_20;
  uint local_1c [2];
  
  local_20 = param_2 + 0xc;
  FUN_002474f4(1,4,&local_20,param_1 + 0x1f14);
  iVar1 = sys_ad_alloc_mem(param_1 + 0x1f1c,4);
  if (iVar1 == 0) {
    uVar2 = mt_serv_reg_eprm_operation(param_1);
    uVar3 = **(uint **)(param_1 + 0x1f1c);
    local_1c[0] = uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 |
                  uVar3 >> 0x18;
    sys_ad_move_mem((void *)(param_2 + 0xe),local_1c,4);
    FUN_00246b90(param_2,6,uVar2);
    sys_ad_free_mem(*(undefined4 *)(param_1 + 0x1f1c));
  }
  else {
    printk("%s: allocate register memory fail\n","hqa_mac_bbp_reg_read");
    FUN_00246b90(param_2,2,0x101);
    uVar2 = 0x101;
  }
  return uVar2;
}

