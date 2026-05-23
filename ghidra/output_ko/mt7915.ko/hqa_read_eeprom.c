// module: mt7915.ko
// function: hqa_read_eeprom @ 0x24afd0
// size: 200 bytes
//

undefined4 hqa_read_eeprom(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  ushort local_1e;
  int local_1c [2];
  
  local_1c[0] = param_2 + 0xc;
  FUN_002474f4(1,2,local_1c,param_1 + 0x1f24);
  iVar1 = sys_ad_alloc_mem(param_1 + 0x1f2c,2);
  if (iVar1 == 0) {
    uVar2 = mt_serv_reg_eprm_operation(param_1,10);
    local_1e = **(ushort **)(param_1 + 0x1f2c) << 8 | **(ushort **)(param_1 + 0x1f2c) >> 8;
    sys_ad_move_mem((void *)(param_2 + 0xe),&local_1e,2);
    FUN_00246b90(param_2,4,uVar2);
    sys_ad_free_mem(*(undefined4 *)(param_1 + 0x1f2c));
  }
  else {
    printk("%s: allocate eeprom memory fail\n","hqa_read_eeprom");
    FUN_00246b90(param_2,2,0x101);
    uVar2 = 0x101;
  }
  return uVar2;
}

