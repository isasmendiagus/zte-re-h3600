// module: tm.ko
// function: zte_api_sw_set_fast_max_entry @ 0x61028
// size: 80 bytes
//

void zte_api_sw_set_fast_max_entry
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  g_v4_fast_entry_up = param_1;
  g_v4_fast_entry_dn = param_2;
  g_v6_total_entry = param_3;
  g_total_fast_entry = param_4;
  printk("v4_fast_entry_up:%d v4_fast_entry_dn:%d  v6_total_entry:%d  total_fast_entry:%d\n",param_1
         ,param_2,param_3,param_4);
  return;
}

