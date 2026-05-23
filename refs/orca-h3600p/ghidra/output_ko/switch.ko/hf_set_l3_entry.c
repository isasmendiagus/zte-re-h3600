// module: switch.ko
// function: hf_set_l3_entry @ 0x12c54
// size: 140 bytes
//

undefined4 hf_set_l3_entry(int param_1)

{
  int iVar1;
  
  if (param_1 == 0) {
    printk("[%s]param is NULL\n","hf_set_l3_entry");
    return 0;
  }
  iVar1 = sw_acl_l3_hardfast_session_add();
  if (iVar1 == 0) {
    return 1;
  }
  iVar1 = __printk_ratelimit("hf_set_l3_entry");
  if (((iVar1 != 0) && (g_switch_debug_level != 0)) &&
     (iVar1 = ___ratelimit(_rs_58169,"hf_set_l3_entry"), iVar1 != 0)) {
    printk("[%s] FAIL\n","hf_set_l3_entry");
  }
  return 0;
}

