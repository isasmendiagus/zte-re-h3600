// module: mt7915.ko
// function: ap_tx_pkt_handle @ 0x1cf4c
// size: 620 bytes
//

int ap_tx_pkt_handle(int param_1,int param_2,int param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  int extraout_r2;
  int *piVar3;
  int iVar4;
  code *pcVar5;
  int extraout_r3;
  
  if (param_2 == 0) {
    iVar2 = *(int *)(param_1 + 0x9db98) + 1;
    *(int *)(param_1 + 0x9db98) = iVar2;
    RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_3 + 0xc),param_3,iVar2,param_4);
    wlan_dbg_set_last_error(0,0,0xb44,"ap_tx_pkt_handle");
    return 1;
  }
  iVar2 = *(int *)(param_2 + 0x904);
  if (*(int *)(param_2 + 0x3fe4) == 0) {
    RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_3 + 0xc),iVar2,param_2 + 0x3000,param_4);
    wlan_dbg_set_last_error(0,0,0xb4f,"ap_tx_pkt_handle");
    return 1;
  }
  cVar1 = *(char *)(param_3 + 5);
  if (*(char *)(*(int *)(param_2 + 0x3fe4) + 4) == '\0') {
    switch(cVar1) {
    case '\x01':
    case '\x02':
      pcVar5 = *(code **)(iVar2 + 0x18);
      break;
    case '\x03':
      pcVar5 = *(code **)(iVar2 + 0x1c);
      break;
    case '\x04':
      pcVar5 = *(code **)(iVar2 + 0x20);
      break;
    case '\x05':
      pcVar5 = *(code **)(iVar2 + 0x24);
      break;
    case '\x06':
      pcVar5 = *(code **)(iVar2 + 0x28);
      break;
    case '\a':
      pcVar5 = *(code **)(iVar2 + 0x2c);
      break;
    default:
      iVar4 = DebugLevel;
      if (-1 < DebugLevel) {
        printk("Send a pacekt was not classified!!\n");
        iVar2 = extraout_r2;
        iVar4 = extraout_r3;
      }
      RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_3 + 0xc),iVar2,iVar4,param_4);
      *(int *)(param_1 + 0x9dba4) = *(int *)(param_1 + 0x9dba4) + 1;
      wlan_dbg_set_last_error(0,0,0xbad,"ap_tx_pkt_handle");
      return 1;
    case '\t':
      pcVar5 = *(code **)(iVar2 + 0x34);
    }
    iVar2 = (*pcVar5)(param_1,param_2,param_3);
    if (iVar2 == 0) {
      wlan_dbg_radio_statistics_inc(0,4);
    }
    else {
      wlan_dbg_set_last_error(0,0,0xbb6,"ap_tx_pkt_handle");
    }
    param_1 = (uint)*(ushort *)(*(int *)(param_3 + 0xc) + 0x42) * 0x14c0 + param_1;
    *(int *)(param_1 + 0xa3078) = *(int *)(param_3 + 0x28) + *(int *)(param_1 + 0xa3078);
    *(int *)(param_1 + 0xa3088) = *(int *)(param_1 + 0xa3088) + 1;
    return iVar2;
  }
  if (cVar1 == '\x04') {
    piVar3 = *(int **)(param_3 + 0x40);
    while (piVar3 != (int *)0x0) {
      iVar2 = *piVar3;
      *piVar3 = 0;
      *(int *)(param_3 + 0x40) = iVar2;
      if (iVar2 == 0) {
        *(undefined4 *)(param_3 + 0x44) = 0;
      }
      *(int *)(param_3 + 0x48) = *(int *)(param_3 + 0x48) + -1;
      iVar4 = *(int *)(param_1 + 0x9db9c) + 1;
      *(int *)(param_1 + 0x9db9c) = iVar4;
      RTMPFreeNdisPacket(param_1,piVar3,iVar2,iVar4,param_4);
      piVar3 = *(int **)(param_3 + 0x40);
    }
  }
  else {
    RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_3 + 0xc),iVar2,cVar1,param_4);
    *(int *)(param_1 + 0x9db9c) = *(int *)(param_1 + 0x9db9c) + 1;
  }
  wlan_dbg_set_last_error(0,0,0xb75,"ap_tx_pkt_handle");
  if (DebugLevel < 4) {
    return 1;
  }
  printk("<--%s(%d)\n","ap_tx_pkt_handle",0xb76);
  return 1;
}

