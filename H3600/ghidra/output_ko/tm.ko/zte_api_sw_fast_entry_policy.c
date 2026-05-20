// module: tm.ko
// function: zte_api_sw_fast_entry_policy @ 0x60824
// size: 48 bytes
//

void zte_api_sw_fast_entry_policy
               (undefined4 *param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4)

{
  *param_1 = g_fast_entry_v4;
  *param_2 = DAT_000d63e4;
  *param_3 = (undefined4)g_fast_entry_v6;
  *param_4 = g_fast_entry_v6._4_4_;
  return;
}

