// module: wlan_debug_module.ko
// function: _pktcnt_dbgflag_read @ 0x11748
// size: 100 bytes
//

undefined4
_pktcnt_dbgflag_read(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  seq_printf(param_1,"dbgflag = 0x%x\n",g_pktcnt_dbgflag,param_4,param_4);
  seq_printf(param_1,"dbgnum = 0x%x\n",g_pktcnt_dbgnum);
  seq_printf(param_1,"g_pktprint_len = 0x%x\n",g_pktprint_len);
  seq_printf(param_1,&_LC30,
             "bit0(0x01/1)  - enable tcp packet count\nbit1(0x02/2)  - enable udp packet count\nbit2(0x04/4)  - enable ping packet print\nbit3(0x08/8)  - enable dhcp packet print\nbit4(0x10/16) - enable arp packet print\nbit5(0x20/32) - enable dns packet print\nbit6(0x40/64) - enable HEX data packet print\nbit7(0x80/128) - enable 1905 packet print\nbit8(0x100/256) - enable LLC packet print\nbit9(0x200/512) - enable IGMP packet print\ne.g.  echo 1/0x01/0X01 > dbgflag,for tcp packet count.\ne.g.  echo 64/0x40/0X40 Numb > dbgflag,for HEX data packet print,Numb is a number bigger than 0 and less than 100,The default message length is 128 bytes.\ne.g.  echo 64/0x40/0X40 Numb Length > dbgflag,for HEX data packet print,if Length is bigger than Actual message length,the message length is Actual message length, otherwise the message length is Length bytes.\n"
            );
  return 0;
}

