// module: wlan_debug_module.ko
// function: _pktcnt_dscp_read @ 0x11674
// size: 148 bytes
//

undefined4 _pktcnt_dscp_read(undefined4 param_1)

{
  seq_printf(param_1," dscp_set_flag  =  %u\n",g_dscp_set_flag);
  seq_printf(param_1,"   dscp_of_tcp  =  %u\n",g_dscp_of_tcp);
  seq_printf(param_1,"   dscp_of_udp  =  %u\n",g_dscp_of_udp);
  seq_printf(param_1,"normal_pkt_cnt  =  %llu\n",(undefined4)g_normal_pkt_cnt,g_normal_pkt_cnt._4_4_
            );
  seq_printf(param_1,"shared_pkt_cnt  =  %llu\n\n",(undefined4)g_shared_pkt_cnt,
             g_shared_pkt_cnt._4_4_);
  seq_printf(param_1,&_LC30,
             "dscp_set_flag   -   set dscp of tcp or(and) udp\n            0   -   disable dscp set\n            1   -   set dscp of tcp\n            2   -   set dscp of udp\n            3   -   set dscp of tcp and udp\n  dscp_of_tcp   -   the dscp value of tcp ( 0 ~ 7 )\n  dscp_of_udp   -   the dscp value of udp ( 0 ~ 7 )\nnormal_pkt_cnt  -   the count of normal pkt\nshared_pkt_cnt  -   the count of shared pkt\ne.g.\necho 0 > dscp       disable dscp set\necho 1 > dscp       set dscp of tcp to the previous value of dscp_of_tcp\necho 2 > dscp       set dscp of udp to the previous value of dscp_of_udp\necho 1 4 > dscp     set dscp of tcp to 4\necho 2 4 > dscp     set dscp of udp to 4\necho 3 4 5 > dscp   set dscp of tcp to 4, and set dscp of udp to 5\n"
            );
  return 0;
}

