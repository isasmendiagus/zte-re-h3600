// module: tm.ko
// function: tm_soft_protocol_iptype_set @ 0x522ac
// size: 140 bytes
//

undefined4
tm_soft_protocol_iptype_set
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  switch(param_1) {
  case 0:
    iVar1 = spa_set_trap_protocol_type0(param_2);
    if (iVar1 == 0) {
      return 0;
    }
    break;
  case 1:
    iVar1 = spa_set_trap_protocol_type1(param_2);
    if (iVar1 == 0) {
      return 0;
    }
    break;
  case 2:
    iVar1 = spa_set_trap_protocol_type2(param_2);
    if (iVar1 == 0) {
      return 0;
    }
    break;
  case 3:
    iVar1 = spa_set_trap_protocol_type3(param_2);
    if (iVar1 == 0) {
      return 0;
    }
    break;
  default:
    printk("tm_soft_protocol_ethtype_set fail, error type_id %d\n",param_1,param_3,param_1,param_4);
    return 0xffffffff;
  }
  printk("tm_soft_protocol_iptype_set fail\n");
  return 0xffffffff;
}

