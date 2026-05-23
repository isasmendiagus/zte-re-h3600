// module: tm.ko
// function: zte_api_pp_set_cpu_queue_rate @ 0x63aa0
// size: 60 bytes
//

undefined4
zte_api_pp_set_cpu_queue_rate
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  tm_protocol_pkt_limit_pps_set(0,param_1,1,param_2,param_4);
  tm_protocol_pkt_limit_pps_set(1,param_1,1,param_2);
  return 0;
}

