// module: mt7915.ko
// function: net_ad_init_wdev @ 0x25b988
// size: 828 bytes
//

undefined4 net_ad_init_wdev(int param_1,int param_2,int param_3)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  undefined2 uVar4;
  int iVar5;
  int iVar6;
  byte *__src;
  byte *local_30;
  
  iVar2 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar2 == 0) {
    return 0x606;
  }
  iVar5 = *(int *)(param_2 + 0x24);
  if (iVar5 == 0) {
    return 0x60a;
  }
  iVar6 = iVar2 + param_3 * 4;
  iVar3 = wdev_init(iVar2,iVar5,0x1000,**(undefined4 **)(iVar6 + 0xc),(int)(char)param_3,0,iVar2);
  if (iVar3 != 1) goto LAB_0025ba3c;
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + iVar2 + 0xc) & 0xffff) == 0x6867 ||
      (*(uint *)("Get_RBIST_IQ_Data_Proc" + iVar2 + 0xc) & 0xffff) == 0x7915) {
    serv_wdev_ops._48_4_ = net_ad_tx_v2;
  }
  iVar3 = wdev_ops_register(iVar5,0x1000,serv_wdev_ops,0);
  if (iVar3 != 1) goto LAB_0025ba3c;
  uVar1 = *(undefined1 *)(param_2 + 0xc50);
  *(undefined1 *)(param_2 + 0x2c) = *(undefined1 *)(iVar5 + 0xc);
  *(undefined1 *)(iVar5 + 0x1a) = uVar1;
  printk("%s: wdev_idx=%d, channel=%d\n","net_ad_init_wdev",*(undefined1 *)(iVar5 + 0xc),uVar1);
  if (*(byte *)(iVar5 + 0x1a) < 0xf) {
    uVar4 = 0x4e;
  }
  else {
    uVar4 = 0xb1;
  }
  *(undefined2 *)(iVar5 + 0x18) = uVar4;
  if (*(char *)(iVar2 + 0x286285) == '\x01') {
    __src = (byte *)(param_2 + 0x111);
LAB_0025bad0:
    if (__src != (byte *)0x0) {
      sys_ad_move_mem((void *)(iVar5 + 0x1b),__src,6);
    }
  }
  else {
    if (*(char *)(iVar2 + 0x286285) == '\0') {
      __src = (byte *)(param_2 + 0xb1);
      goto LAB_0025bad0;
    }
    __src = (byte *)0x0;
  }
  iVar3 = wdev_do_open(iVar5);
  if (iVar3 != 1) goto LAB_0025ba3c;
  if (*(char *)(iVar2 + 0x286285) == '\x01') {
    local_30 = (byte *)(param_2 + 0xb1);
LAB_0025bb24:
    if (local_30 != (byte *)0x0) {
      sys_ad_move_mem((void *)(iVar5 + 0x21),local_30,6);
    }
  }
  else {
    if (*(char *)(iVar2 + 0x286285) == '\0') {
      local_30 = (byte *)(param_2 + 0x51);
      goto LAB_0025bb24;
    }
    local_30 = (byte *)0x0;
  }
  iVar5 = wifi_sys_linkup(iVar5,0);
  if (iVar5 == 1) {
    iVar5 = *(int *)(param_2 + 0x28);
    if (iVar5 == 0) {
      return 0x60a;
    }
    iVar3 = wdev_init(iVar2,iVar5,0x800,**(undefined4 **)(iVar6 + 0xc),(int)(char)param_3,0,iVar2);
    if (iVar3 == 1) {
      if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + iVar2 + 0xc) & 0xffff) == 0x6867 ||
          (*(uint *)("Get_RBIST_IQ_Data_Proc" + iVar2 + 0xc) & 0xffff) == 0x7915) {
        serv_wdev_ops._48_4_ = net_ad_tx_v2;
      }
      iVar3 = wdev_ops_register(iVar5,0x800,serv_wdev_ops,0);
      if (iVar3 == 1) {
        *(undefined1 *)(iVar5 + 0x1a) = *(undefined1 *)(param_2 + 0xc50);
        printk("%s: wdev_idx=%d, channel=%d\n","net_ad_init_wdev",*(undefined1 *)(iVar5 + 0xc));
        if (*(byte *)(iVar5 + 0x1a) < 0xf) {
          uVar4 = 0x4e;
        }
        else {
          uVar4 = 0xb1;
        }
        *(undefined2 *)(iVar5 + 0x18) = uVar4;
        if (*(char *)(iVar2 + 0x286285) == '\x01') {
          __src = (byte *)(param_2 + 0x111);
        }
        else if (*(char *)(iVar2 + 0x286285) == '\0') {
          __src = (byte *)(param_2 + 0xb1);
        }
        if (__src != (byte *)0x0) {
          *__src = *__src | 2;
          sys_ad_move_mem((void *)(iVar5 + 0x1b),__src,6);
        }
        iVar3 = wdev_do_open(iVar5);
        if (iVar3 == 1) {
          if (*(char *)(iVar2 + 0x286285) == '\x01') {
            local_30 = (byte *)(param_2 + 0xb1);
          }
          else if (*(char *)(iVar2 + 0x286285) == '\0') {
            local_30 = (byte *)(param_2 + 0x51);
          }
          if (local_30 != (byte *)0x0) {
            *local_30 = *local_30 | 2;
            sys_ad_move_mem((void *)(iVar5 + 0x21),local_30,6);
          }
          iVar2 = wifi_sys_linkup(iVar5,0);
          if (iVar2 == 1) {
            return 0;
          }
        }
      }
    }
  }
LAB_0025ba3c:
  printk("%s: inits wdev failed!\n","net_ad_init_wdev");
  return 0x602;
}

