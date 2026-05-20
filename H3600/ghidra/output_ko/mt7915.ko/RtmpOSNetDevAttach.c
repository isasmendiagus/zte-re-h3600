// module: mt7915.ko
// function: RtmpOSNetDevAttach @ 0x2442e8
// size: 364 bytes
//

bool RtmpOSNetDevAttach(int param_1,int param_2,undefined4 *param_3)

{
  char cVar1;
  int iVar2;
  undefined1 *puVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_2 + 300);
  if (2 < DebugLevel) {
    printk("RtmpOSNetDevAttach()--->\n");
  }
  if (param_3 == (undefined4 *)0x0) {
    *(undefined4 *)(iVar4 + 0x24) = 0;
  }
  else {
    *(undefined4 *)(iVar4 + 8) = *param_3;
    *(undefined4 *)(iVar4 + 0xc) = param_3[1];
    *(undefined4 *)(iVar4 + 0x10) = param_3[2];
    *(undefined4 *)(iVar4 + 0x28) = param_3[3];
    *(undefined **)(param_2 + 0x130) = &DAT_005e03fc;
    if (param_3[4] != 0) {
      *(undefined4 *)(iVar4 + 0x40) = param_3[4];
    }
    *(uint *)(param_2 + 0x4c8) = (uint)*(ushort *)(param_3 + 9);
    if (param_1 == 0) {
      puVar3 = rt28xx_iw_handler_def;
      param_3[7] = rt28xx_iw_handler_def;
LAB_00244370:
      *(undefined1 **)(param_2 + 0x124) = puVar3;
    }
    else {
      if (param_1 == 1) {
        puVar3 = rt28xx_ap_iw_handler_def;
        param_3[7] = rt28xx_ap_iw_handler_def;
        goto LAB_00244370;
      }
      puVar3 = (undefined1 *)param_3[7];
      if (puVar3 != (undefined1 *)0x0) goto LAB_00244370;
    }
    memmove(*(void **)(param_2 + 0x1dc),param_3 + 10,6);
    cVar1 = *(char *)((int)param_3 + 0x3e);
    *(undefined4 *)(iVar4 + 0x24) = 0;
    if (cVar1 != '\0') {
      iVar2 = register_netdevice(param_2);
      iVar4 = *(int *)(param_2 + 0x240);
      goto joined_r0x002443fc;
    }
  }
  iVar2 = register_netdev(param_2);
  iVar4 = *(int *)(param_2 + 0x240);
joined_r0x002443fc:
  if (iVar4 == 0) {
    warn_slowpath_null("include/linux/netdevice.h",0xa06);
    printk(&_LC21);
  }
  else {
    _set_bit(0,iVar4 + 0x50);
  }
  if (2 < DebugLevel) {
    printk("<---RtmpOSNetDevAttach(), ret=%d\n",iVar2);
  }
  return iVar2 != 0;
}

