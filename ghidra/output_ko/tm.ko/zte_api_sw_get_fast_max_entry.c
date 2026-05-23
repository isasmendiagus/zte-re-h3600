// module: tm.ko
// function: zte_api_sw_get_fast_max_entry @ 0x60854
// size: 28 bytes
//

void zte_api_sw_get_fast_max_entry(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  *param_1 = g_v4_fast_entry_up;
  uVar2 = g_total_fast_entry;
  uVar1 = g_v6_total_entry;
  param_1[1] = g_v4_fast_entry_dn;
  param_1[2] = uVar1;
  param_1[3] = uVar2;
  return;
}

