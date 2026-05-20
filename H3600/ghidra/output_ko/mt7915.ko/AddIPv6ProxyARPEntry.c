// module: mt7915.ko
// function: AddIPv6ProxyARPEntry @ 0x22628c
// size: 808 bytes
//

undefined4
AddIPv6ProxyARPEntry(undefined4 param_1,undefined4 *param_2,void *param_3,void *param_4,int param_5)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined1 *puVar4;
  int iVar5;
  undefined2 local_2e;
  int *local_2c [2];
  
  local_2e = 0x80fe;
  uVar2 = *param_2;
  if (-1 < DebugLevel) {
    printk(&_LC4,"AddIPv6ProxyARPEntry");
  }
  if (param_5 == 0) {
    _raw_spin_lock_bh(param_2 + 0x1329);
    local_2c[0] = (int *)param_2[0x132c];
    if (local_2c[0] != param_2 + 0x132c) goto LAB_002262f0;
  }
  else {
    local_2c[0] = (int *)param_2[0x132c];
    if (local_2c[0] == param_2 + 0x132c) goto LAB_002263bc;
LAB_002262f0:
    do {
      piVar3 = local_2c[0];
      iVar1 = memcmp(local_2c[0] + 2,param_3,6);
      if (iVar1 == 0) {
        iVar1 = memcmp((void *)((int)piVar3 + 0xf),param_4,0x10);
        if (iVar1 == 0) {
          if (0 < DebugLevel) {
            printk("%s, the Mac address and IPv6 Address exactly same as the one in List already!\n"
                   ,"AddIPv6ProxyARPEntry");
          }
          if (param_5 == 0) {
            _raw_spin_unlock_bh(param_2 + 0x1329);
            return 0;
          }
          return 0;
        }
      }
      else {
        iVar1 = memcmp((void *)((int)piVar3 + 0xf),param_4,0x10);
        if (iVar1 == 0) {
          if (0 < DebugLevel) {
            printk("%s, different Mac address use IPv6 address which already in List!\n",
                   "AddIPv6ProxyARPEntry");
          }
          if (param_5 == 0) {
            _raw_spin_unlock_bh(param_2 + 0x1329);
          }
          wext_send_proxy_arp_event
                    (uVar2,param_3,(int)local_2c[0] + 0xf,local_2c[0] + 2,(int)local_2c[0] + 0xf,1,0
                     ,1);
          return 0;
        }
      }
      local_2c[0] = (int *)*piVar3;
    } while (local_2c[0] != param_2 + 0x132c);
    if (param_5 != 0) goto LAB_002263bc;
  }
  _raw_spin_unlock_bh(param_2 + 0x1329);
LAB_002263bc:
  os_alloc_mem(0,local_2c,0x20);
  piVar3 = local_2c[0];
  if (local_2c[0] == (int *)0x0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s Not available memory\n","AddIPv6ProxyARPEntry");
    uVar2 = 0;
  }
  else {
    puVar4 = (undefined1 *)((int)param_3 + -1);
    memmove(local_2c[0] + 2,param_3,6);
    iVar1 = memcmp(&local_2e,param_4,2);
    if (iVar1 == 0) {
      *(undefined1 *)((int)piVar3 + 0xe) = 0;
    }
    else {
      *(undefined1 *)((int)piVar3 + 0xe) = 1;
    }
    memmove((void *)((int)piVar3 + 0xf),param_4,0x10);
    iVar1 = 0;
    do {
      iVar5 = iVar1 + 1;
      puVar4 = puVar4 + 1;
      printk("pTargetMACAddr[%i] = %x\n",iVar1,*puVar4);
      iVar1 = iVar5;
    } while (iVar5 != 6);
    puVar4 = (undefined1 *)((int)param_4 + -1);
    iVar1 = 0;
    do {
      iVar5 = iVar1 + 1;
      puVar4 = puVar4 + 1;
      printk("pTargetIPv6Addr[%i] = %x\n",iVar1,*puVar4);
      iVar1 = iVar5;
    } while (iVar5 != 0x10);
    if (param_5 == 0) {
      _raw_spin_lock_bh(param_2 + 0x1329);
      piVar3 = (int *)param_2[0x132d];
      *local_2c[0] = *piVar3;
      local_2c[0][1] = (int)piVar3;
      *(int **)(*piVar3 + 4) = local_2c[0];
      *piVar3 = (int)local_2c[0];
      _raw_spin_unlock_bh(param_2 + 0x1329);
      return 1;
    }
    piVar3 = (int *)param_2[0x132d];
    uVar2 = 1;
    *local_2c[0] = *piVar3;
    local_2c[0][1] = (int)piVar3;
    *(int **)(*piVar3 + 4) = local_2c[0];
    *piVar3 = (int)local_2c[0];
  }
  return uVar2;
}

