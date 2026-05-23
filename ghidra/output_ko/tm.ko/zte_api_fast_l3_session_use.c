// module: tm.ko
// function: zte_api_fast_l3_session_use @ 0x638d8
// size: 188 bytes
//

undefined4 zte_api_fast_l3_session_use(undefined4 param_1,uint *param_2,undefined1 *param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_28 [4];
  uint uStack_24;
  uint uStack_20;
  uint local_1c;
  uint local_18;
  uint local_14;
  
  __memzero(&uStack_24,0x14);
  uStack_20 = param_2[1];
  local_1c = param_2[2];
  local_18 = param_2[3];
  local_14 = param_2[4];
  uStack_24 = *param_2 & 0xfff;
  _raw_spin_lock_bh(&fast_api_busy_lock);
  iVar1 = tm_get_acl_flow_status(&uStack_24,local_28);
  if (iVar1 == 0) {
    _raw_spin_unlock_bh(&fast_api_busy_lock);
    *param_3 = local_28[0];
    uVar2 = 0;
  }
  else {
    if (g_tm_debug_level != 0) {
      printk("[%s] tm_get_acl_flow_status failed %d\n","zte_sw_api.c",iVar1);
    }
    _raw_spin_unlock_bh(&fast_api_busy_lock);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

