// module: switch.ko
// function: hf_query_l3_status @ 0x13014
// size: 76 bytes
//

undefined4 hf_query_l3_status(int param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (param_2 != (undefined4 *)0x0 && param_1 != 0) {
    iVar1 = sw_acl_l3_hardfast_flowstatus();
    if (iVar1 == 1) {
      *param_2 = 1;
    }
    else {
      *param_2 = 0;
    }
    return 1;
  }
  printk("[%s]param is NULL\n","hf_query_l3_status",param_3,param_4,param_4);
  return 0;
}

