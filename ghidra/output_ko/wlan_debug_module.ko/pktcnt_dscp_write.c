// module: wlan_debug_module.ko
// function: pktcnt_dscp_write @ 0x12828
// size: 704 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint pktcnt_dscp_write(int param_1,uint param_2,uint param_3)

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
    if (iVar2 != 0) goto LAB_000129e0;
  }
  else if (param_3 != 0) {
    __memzero(__s,param_3,uVar4);
LAB_000129e0:
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
  _pktcnt_Extract_parameters_constprop_2(&local_36,&g_dscp_set_flag);
  if (3 < g_dscp_set_flag) {
    printk("error: The value of dscp_set_flag is out of range! (0 ~ 3)\n");
    g_dscp_set_flag = 0;
    goto LAB_00012964;
  }
  sVar1 = strnlen(local_2c,10);
  if (sVar1 == 0) {
LAB_00012914:
    if (g_dscp_set_flag == 0) goto LAB_00012a9c;
    if (g_dscp_set_flag == 1) {
      printk("set dscp of tcp to %d\n",g_dscp_of_tcp);
    }
    else if (g_dscp_set_flag == 2) {
      printk("set dscp of udp to %d\n",g_dscp_of_udp);
    }
    else {
LAB_0001299c:
      printk("set dscp of tcp to %d\n",g_dscp_of_tcp);
      printk("set dscp of udp to %d\n",g_dscp_of_udp);
    }
  }
  else {
    if (g_dscp_set_flag == 1) {
      _pktcnt_Extract_parameters_constprop_2(local_2c,&g_dscp_of_tcp);
      if (7 < g_dscp_of_tcp) {
LAB_00012a78:
        printk("error: The value of dscp_of_tcp is out of range! (0 ~ 7)\n");
        g_dscp_set_flag = 0;
        g_dscp_of_tcp = 0;
        goto LAB_00012964;
      }
      goto LAB_00012914;
    }
    if (g_dscp_set_flag == 2) {
      _pktcnt_Extract_parameters_constprop_2(local_2c,&g_dscp_of_udp);
LAB_00012a18:
      if (7 < g_dscp_of_udp) {
        printk("error: The value of dscp_of_udp is out of range! (0 ~ 7)\n");
        g_dscp_set_flag = 0;
        g_dscp_of_udp = 0;
        goto LAB_00012964;
      }
      goto LAB_00012914;
    }
    if (g_dscp_set_flag == 3) {
      sVar1 = strnlen(__string,10);
      if (sVar1 == 0) {
        printk("error: please input the dscp of udp (0 ~ 7)\n");
        g_dscp_set_flag = 0;
        goto LAB_00012964;
      }
      _pktcnt_Extract_parameters_constprop_2(local_2c,&g_dscp_of_tcp);
      _pktcnt_Extract_parameters_constprop_2(__string,&g_dscp_of_udp);
      if (7 < g_dscp_of_tcp) goto LAB_00012a78;
      goto LAB_00012a18;
    }
    if (g_dscp_set_flag != 0) goto LAB_0001299c;
LAB_00012a9c:
    printk("disable dscp set\n");
  }
  if (_init_timer_key == (code *)0x0) {
    _init_timer_key = wlan_debug_pktcount;
  }
LAB_00012964:
  kfree(__s);
  return param_3;
}

