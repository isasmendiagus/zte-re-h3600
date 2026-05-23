// module: mt7915.ko
// function: net_ad_write_ca53_reg @ 0x25d8c4
// size: 80 bytes
//

void net_ad_write_ca53_reg(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 local_c;
  
  uVar1 = __arm_ioremap(*param_1,0x10,0);
  *param_1 = uVar1;
  sys_ad_move_mem(&local_c,param_1,4);
  sys_io_write32(local_c,*(undefined4 *)param_1[2]);
  __arm_iounmap(local_c);
  return;
}

