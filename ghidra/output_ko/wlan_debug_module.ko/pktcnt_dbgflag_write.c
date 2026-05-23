// module: wlan_debug_module.ko
// function: pktcnt_dbgflag_write @ 0x12518
// size: 516 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint pktcnt_dbgflag_write(int param_1,uint param_2,uint param_3)

{
  char *__s;
  size_t sVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  char *__string;
  char *local_40 [2];
  undefined2 local_36;
  undefined2 local_34;
  undefined2 local_32;
  undefined2 local_30;
  undefined2 local_2e;
  char local_2c [20];
  
  __s = (char *)__kmalloc(param_3 + 1,0x80d0);
  if (__s == (char *)0x0) {
    return 0xfffffff4;
  }
  uVar5 = *(uint *)(((uint)local_40 & 0xffffe000) + 8);
  uVar3 = param_2 + param_3;
  uVar4 = uVar3;
  if (!CARRY4(param_2,param_3)) {
    uVar4 = uVar3 - (uVar5 + 1);
  }
  if (!CARRY4(param_2,param_3) && uVar3 <= uVar5) {
    uVar5 = 0;
  }
  if (uVar5 == 0) {
    iVar2 = __copy_from_user(__s,param_2,param_3);
    if (iVar2 != 0) goto LAB_000126ec;
  }
  else if (param_3 != 0) {
    __memzero(__s,param_3,uVar4);
LAB_000126ec:
    kfree(__s);
    return 0xfffffff2;
  }
  __s[param_3] = '\0';
  PDE_DATA(*(undefined4 *)(param_1 + 0x10));
  __string = local_2c + 10;
  local_36 = 0;
  local_34 = 0;
  local_32 = 0;
  local_30 = 0;
  local_2e = 0;
  local_2c[0] = '\0';
  local_2c[1] = '\0';
  local_2c[2] = '\0';
  local_2c[3] = '\0';
  local_2c[4] = '\0';
  local_2c[5] = '\0';
  local_2c[6] = '\0';
  local_2c[7] = '\0';
  local_2c[8] = '\0';
  local_2c[9] = '\0';
  local_2c[10] = '\0';
  local_2c[0xb] = '\0';
  local_2c[0xc] = '\0';
  local_2c[0xd] = '\0';
  local_2c[0xe] = '\0';
  local_2c[0xf] = '\0';
  local_2c[0x10] = '\0';
  local_2c[0x11] = '\0';
  local_2c[0x12] = '\0';
  local_2c[0x13] = '\0';
  local_40[0] = __string;
  sscanf(__s,"%9s%9s%9s",&local_36,local_2c);
  _pktcnt_Extract_parameters_constprop_2(&local_36,&g_pktcnt_dbgflag);
  sVar1 = strnlen(local_2c,10);
  if (sVar1 != 0) {
    _pktcnt_Extract_parameters_constprop_2(local_2c,&g_pktcnt_dbgnum);
    sVar1 = strnlen(__string,10);
    if (sVar1 == 0) {
      g_pktprint_len = 0x80;
    }
    else {
      _pktcnt_Extract_parameters_constprop_2(__string,&g_pktprint_len);
    }
  }
  if (100 < g_pktcnt_dbgnum) {
    g_pktcnt_dbgnum = 100;
    printk("set dbgnum show less than 100\n");
  }
  g_count = 0;
  printk("set g_count = [0x%x]\n",0);
  printk("set dbgflag = [0x%x]\n",g_pktcnt_dbgflag);
  printk("set dbgnum = [0x%x]\n",g_pktcnt_dbgnum);
  printk("set g_pktprint_len = [0x%x]\n",g_pktprint_len);
  printk(&_LC30,
         "bit0(0x01/1)  - enable tcp packet count\nbit1(0x02/2)  - enable udp packet count\nbit2(0x04/4)  - enable ping packet print\nbit3(0x08/8)  - enable dhcp packet print\nbit4(0x10/16) - enable arp packet print\nbit5(0x20/32) - enable dns packet print\nbit6(0x40/64) - enable HEX data packet print\nbit7(0x80/128) - enable 1905 packet print\nbit8(0x100/256) - enable LLC packet print\nbit9(0x200/512) - enable IGMP packet print\ne.g.  echo 1/0x01/0X01 > dbgflag,for tcp packet count.\ne.g.  echo 64/0x40/0X40 Numb > dbgflag,for HEX data packet print,Numb is a number bigger than 0 and less than 100,The default message length is 128 bytes.\ne.g.  echo 64/0x40/0X40 Numb Length > dbgflag,for HEX data packet print,if Length is bigger than Actual message length,the message length is Actual message length, otherwise the message length is Length bytes.\n"
        );
  if (_init_timer_key == (code *)0x0) {
    _init_timer_key = wlan_debug_pktcount;
  }
  kfree(__s);
  return param_3;
}

