// module: mt7915.ko
// function: set_veri_pkt_ctrl_assign @ 0x1d6d08
// size: 980 bytes
//

undefined4 set_veri_pkt_ctrl_assign(int param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  undefined1 uVar2;
  ushort uVar3;
  undefined2 uVar4;
  char *pcVar5;
  char *__s;
  char *__s_00;
  char *__s_01;
  char *__s_02;
  char *pcVar6;
  undefined4 local_34;
  uint local_30;
  undefined4 local_2c;
  
  __memzero(&local_34,0xc,param_3,param_4,0);
  if (param_2 == (char *)0x0) {
    return 1;
  }
  pcVar5 = strstr(param_2,"du:");
  __s = strstr(param_2,"sn:");
  __s_00 = strstr(param_2,"pid:");
  __s_01 = strstr(param_2,"pm:");
  __s_02 = strstr(param_2,"life:");
  pcVar6 = strstr(param_2,"htc:");
  if (pcVar6 != (char *)0x0) {
    if ((*(uint *)(param_1 + 0xa7cc58) & 0x2000) == 0) {
      if (-1 < DebugLevel) {
        printk("enable htc control in first\n");
      }
    }
    else {
      pcVar6 = strchr(pcVar6,0x3a);
      local_34 = os_str_tol(pcVar6 + 1,0,0x10);
    }
  }
  if (pcVar5 != (char *)0x0) {
    if ((*(uint *)(param_1 + 0xa7cc58) & 0x10) == 0) {
      if (-1 < DebugLevel) {
        printk("enable dur control in first\n");
      }
    }
    else {
      pcVar5 = strchr(pcVar5,0x3a);
      uVar4 = os_str_tol(pcVar5 + 1,0,10);
      local_30 = CONCAT22(uVar4,(undefined2)local_30) & 0xffffff;
    }
  }
  if (__s != (char *)0x0) {
    if ((*(uint *)(param_1 + 0xa7cc58) & 8) == 0) {
      if (-1 < DebugLevel) {
        printk("enable sn control in first\n");
      }
    }
    else {
      pcVar5 = strchr(__s,0x3a);
      uVar3 = os_str_tol(pcVar5 + 1,0,10);
      if (0xfff < uVar3) {
        if (-1 < DebugLevel) {
          printk("%s: seq:%u over spec\n","set_veri_pkt_ctrl_assign");
          return 0;
        }
        return 0;
      }
      local_30 = CONCAT22(local_30._2_2_,uVar3);
    }
  }
  if (__s_00 != (char *)0x0) {
    if ((*(uint *)(param_1 + 0xa7cc58) & 0xc00) == 0) {
      if (-1 < DebugLevel) {
        printk("enable txs2m/txs2h control in first\n");
      }
    }
    else {
      pcVar5 = strchr(__s_00,0x3a);
      uVar2 = os_str_tol(pcVar5 + 1,0,10);
      local_2c = CONCAT31(local_2c._1_3_,uVar2);
    }
  }
  if (__s_01 != (char *)0x0) {
    if ((*(uint *)(param_1 + 0xa7cc58) & 4) == 0) {
      if (-1 < DebugLevel) {
        printk("enable pm control in first\n");
      }
    }
    else {
      pcVar5 = strchr(__s_01,0x3a);
      bVar1 = os_str_tol(pcVar5 + 1,0,10);
      if (1 < bVar1) {
        if (-1 < DebugLevel) {
          printk("%s: pm:%u over spec\n","set_veri_pkt_ctrl_assign");
        }
        return 0;
      }
      local_2c._0_2_ = CONCAT11(bVar1,(undefined1)local_2c);
    }
  }
  if (__s_02 != (char *)0x0) {
    if ((*(uint *)(param_1 + 0xa7cc58) & 0x1000) == 0) {
      if (-1 < DebugLevel) {
        printk("enable assigned_pkt_lifetime control in first\n");
      }
    }
    else {
      pcVar5 = strchr(__s_02,0x3a);
      uVar2 = os_str_tol(pcVar5 + 1,0,10);
      local_2c._0_3_ = CONCAT12(uVar2,(undefined2)local_2c);
    }
  }
  *(undefined4 *)(param_1 + 0xa7d084) = local_34;
  *(uint *)(param_1 + 0xa7d088) = local_30;
  *(undefined4 *)(param_1 + 0xa7d08c) = local_2c;
  return 1;
}

