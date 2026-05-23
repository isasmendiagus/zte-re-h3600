// module: mt7915.ko
// function: IPv6ProxyARP @ 0x226bcc
// size: 324 bytes
//

undefined4
IPv6ProxyARP(undefined4 param_1,undefined4 *param_2,int param_3,undefined4 param_4,int param_5)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  
  uVar3 = *param_2;
  if (param_5 == 0) {
    _raw_spin_lock_bh(param_2 + 0x1329);
    piVar2 = (int *)param_2[0x132c];
    if (piVar2 == param_2 + 0x132c) goto LAB_00226ca4;
  }
  else {
    piVar2 = (int *)param_2[0x132c];
    if (piVar2 == param_2 + 0x132c) {
      return 0;
    }
  }
  do {
    iVar1 = memcmp((void *)((int)piVar2 + 0xf),(void *)(param_3 + 0x32),0x10);
    if (iVar1 == 0) {
      if (param_5 == 0) {
        _raw_spin_unlock_bh(param_2 + 0x1329);
      }
      if (0 < DebugLevel) {
        printk(&_LC4,"IPv6ProxyARP");
      }
      wext_send_proxy_arp_event
                (uVar3,param_3 + 0x44,param_3 + 10,piVar2 + 2,(void *)((int)piVar2 + 0xf),1,param_4,
                 0);
      return 1;
    }
    piVar2 = (int *)*piVar2;
  } while (param_2 + 0x132c != piVar2);
  if (param_5 != 0) {
    return 0;
  }
LAB_00226ca4:
  _raw_spin_unlock_bh(param_2 + 0x1329);
  return 0;
}

