// module: mt7915.ko
// function: IPv4ProxyARP @ 0x22669c
// size: 1324 bytes
//

undefined4 IPv4ProxyARP(undefined4 param_1,undefined4 *param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  undefined4 uVar2;
  void *__s2;
  void *__s1;
  undefined4 *puVar3;
  void *__s1_00;
  undefined4 *puVar4;
  undefined1 local_32;
  undefined1 local_31;
  undefined1 local_30;
  undefined1 local_2f;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined1 local_2c;
  undefined1 local_2b;
  undefined1 local_2a;
  undefined1 local_29;
  
  uVar2 = *param_2;
  __s1_00 = (void *)(param_3 + 0x10);
  __s2 = (void *)(param_3 + 10);
  __s1 = (void *)(param_3 + 0x14);
  local_2e = 0;
  local_2d = 0;
  local_2c = 0;
  local_2b = 0;
  local_2a = 0;
  local_29 = 0;
  local_32 = 0;
  local_31 = 0;
  local_30 = 0;
  local_2f = 0;
  if (2 < DebugLevel) {
    printk("%s  wdev_idx %d TargetIP %d:%d:%d:%d\n","IPv4ProxyARP",*(undefined1 *)(param_2 + 3),
           *(undefined1 *)(param_3 + 0x1a),*(undefined1 *)(param_3 + 0x1b),
           *(undefined1 *)(param_3 + 0x1c),*(undefined1 *)(param_3 + 0x1d));
  }
  if (param_5 == 0) {
    _raw_spin_lock_bh(param_2 + 0x1328);
    puVar4 = (undefined4 *)param_2[0x132a];
    if (puVar4 != param_2 + 0x132a) goto LAB_0022674c;
LAB_002267ec:
    _raw_spin_unlock_bh(param_2 + 0x1328);
  }
  else {
    puVar4 = (undefined4 *)param_2[0x132a];
    if (puVar4 != param_2 + 0x132a) {
LAB_0022674c:
      do {
        puVar3 = param_2 + 0x132a;
        iVar1 = memcmp((void *)((int)puVar4 + 0xe),(void *)(param_3 + 0x1a),4);
        if (iVar1 == 0) {
          iVar1 = memcmp(puVar4 + 2,__s2,6);
          if ((iVar1 == 0) ||
             ((iVar1 = memcmp(__s1,&BROADCAST_ADDR,6), iVar1 != 0 &&
              (iVar1 = memcmp(__s1,&local_2e,6), iVar1 != 0)))) {
            if (param_5 == 0) {
LAB_002267c8:
              _raw_spin_unlock_bh(param_2 + 0x1328);
            }
            iVar1 = memcmp(__s1_00,&local_32,4);
            if (iVar1 == 0) {
              return 1;
            }
LAB_002268fc:
            iVar1 = 0;
          }
          else {
            iVar1 = memcmp(__s1_00,&local_32,4);
            if (iVar1 != 0) {
              if (param_5 == 0) goto LAB_002267c8;
              goto LAB_002268fc;
            }
            if (2 < DebugLevel) {
              printk("%s, Found DAD!!!!\n","IPv4ProxyARP");
            }
            printk("found dad...\n");
            if (param_5 == 0) {
              iVar1 = 1;
              _raw_spin_unlock_bh(param_2 + 0x1328);
            }
            else {
              iVar1 = 1;
            }
          }
          if (2 < DebugLevel) {
            printk("%s  TargetIP %d:%d:%d:%d indicate to daemon\n","IPv4ProxyARP",
                   *(undefined1 *)(param_3 + 0x1a),*(undefined1 *)(param_3 + 0x1b),
                   *(undefined1 *)(param_3 + 0x1c),*(undefined1 *)(param_3 + 0x1d));
          }
          wext_send_proxy_arp_event
                    (uVar2,__s2,__s1_00,puVar4 + 2,(void *)((int)puVar4 + 0xe),0,param_4,iVar1);
          if (iVar1 != 0 || param_4 != 0) {
            return 1;
          }
          if (param_5 != 0) {
            puVar4 = (undefined4 *)param_2[0x132a];
            if (puVar4 == puVar3) goto LAB_00226a2c;
            goto LAB_00226970;
          }
          _raw_spin_lock_bh(param_2 + 0x1328);
          puVar4 = (undefined4 *)param_2[0x132a];
          if (puVar4 == puVar3) goto LAB_00226a24;
LAB_00226970:
          do {
            iVar1 = memcmp((void *)((int)puVar4 + 0xe),__s1_00,4);
            if (iVar1 == 0) {
              if (param_5 == 0) {
                _raw_spin_unlock_bh(param_2 + 0x1328);
                return 1;
              }
              return 1;
            }
            puVar4 = (undefined4 *)*puVar4;
          } while (puVar4 != puVar3);
          if (param_5 == 0) {
LAB_00226a24:
            _raw_spin_unlock_bh(param_2 + 0x1328);
          }
LAB_00226a2c:
          AddIPv4ProxyARPEntry(param_1,param_2,__s2,__s1_00,param_5);
          if (DebugLevel < 0) {
            return 1;
          }
          printk("%s, New Station take arp request, Learning ARP Entry from it\n","IPv4ProxyARP");
          return 1;
        }
        puVar4 = (undefined4 *)*puVar4;
      } while (puVar4 != puVar3);
      if (param_5 == 0) goto LAB_002267ec;
    }
  }
  puVar4 = param_2 + 0x132a;
  iVar1 = memcmp(__s1,&BROADCAST_ADDR,6);
  if ((iVar1 != 0) && (iVar1 = memcmp(__s1,&local_2e,6), iVar1 != 0)) {
    return 0;
  }
  if (param_4 != 0) {
    return 0;
  }
  iVar1 = memcmp(__s1_00,&local_32,4);
  if (iVar1 == 0) {
    AddIPv4ProxyARPEntry(param_1,param_2,__s2,(void *)(param_3 + 0x1a),param_5);
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s, New Station take DAD to detect, Learning ARP Entry from it\n","IPv4ProxyARP");
    return 0;
  }
  if (param_5 == 0) {
    _raw_spin_lock_bh(param_2 + 0x1328);
    puVar3 = (undefined4 *)param_2[0x132a];
    if (puVar4 != puVar3) goto LAB_00226860;
  }
  else {
    puVar3 = (undefined4 *)param_2[0x132a];
    if (puVar4 == puVar3) goto LAB_00226a88;
LAB_00226860:
    do {
      iVar1 = memcmp((void *)((int)puVar3 + 0xe),__s1_00,4);
      if (iVar1 == 0) {
        if (param_5 == 0) {
          _raw_spin_unlock_bh(param_2 + 0x1328);
          return 0;
        }
        return 0;
      }
      puVar3 = (undefined4 *)*puVar3;
    } while (puVar4 != puVar3);
    if (param_5 != 0) goto LAB_00226a88;
  }
  _raw_spin_unlock_bh(param_2 + 0x1328);
LAB_00226a88:
  AddIPv4ProxyARPEntry(param_1,param_2,__s2,__s1_00,param_5);
  if (-1 < DebugLevel) {
    printk("%s, New Station take arp request to detect, Learning ARP Entry from it\n","IPv4ProxyARP"
          );
  }
  return 0;
}

