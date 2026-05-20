// module: mt7915.ko
// function: hqa_write_eeprom @ 0x24c69c
// size: 208 bytes
//

undefined4 hqa_write_eeprom(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_1e [2];
  int local_1c [2];
  
  local_1c[0] = param_2 + 0xc;
  FUN_002474f4(1,2,local_1c,param_1 + 0x1f24);
  FUN_002474f4(1,2,local_1c,auStack_1e);
  iVar1 = sys_ad_alloc_mem(param_1 + 0x1f2c,2);
  if (iVar1 == 0) {
    sys_ad_move_mem(*(void **)(param_1 + 0x1f2c),auStack_1e,2);
    uVar2 = mt_serv_reg_eprm_operation(param_1,0xb);
    FUN_00246b90(param_2,2,uVar2);
    sys_ad_free_mem(*(undefined4 *)(param_1 + 0x1f2c));
  }
  else {
    printk("%s: allocate eeprom memory fail\n","hqa_write_eeprom");
    FUN_00246b90(param_2,2,0x101);
    uVar2 = 0x101;
  }
  return uVar2;
}

