// module: mt7915.ko
// function: RTMPSetPhyMode @ 0xdbce4
// size: 312 bytes
//

void RTMPSetPhyMode(int param_1,int param_2,undefined4 param_3)

{
  byte *pbVar1;
  undefined4 uVar2;
  byte *pbVar3;
  char cVar4;
  uint uVar5;
  uint uVar6;
  
  uVar2 = wmode_2_rfic(param_3);
  uVar6 = (uint)*(byte *)(param_2 + 0x1a);
  if (uVar6 == 0) {
    uVar6 = HcGetChannelByRf(param_1,uVar2);
  }
  uVar2 = HcGetBandByWdev(param_2);
  pbVar3 = (byte *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar2);
  pbVar1 = pbVar3 + 0x49c;
  if (*pbVar1 != 0) {
    if (*pbVar3 != uVar6) {
      uVar5 = 0;
      do {
        uVar5 = uVar5 + 1;
        if (uVar5 == *pbVar1) goto LAB_000dbd5c;
        pbVar3 = pbVar3 + 0x14;
      } while (*pbVar3 != uVar6);
    }
    goto LAB_000dbd9c;
  }
LAB_000dbd5c:
  cVar4 = *(char *)(param_1 + 0x286285);
  if (cVar4 == '\x01') {
    if (uVar6 != 0) {
      uVar6 = FirstChannel(param_1,param_2);
      cVar4 = *(char *)(param_1 + 0x286285);
      goto LAB_000dbd70;
    }
  }
  else {
LAB_000dbd70:
    if (cVar4 == '\0') {
      uVar6 = FirstChannel(param_1,param_2);
    }
  }
  if (-1 < DebugLevel) {
    printk("%s(): channel out of range, use first ch=%d\n","RTMPSetPhyMode",uVar6);
  }
  *(char *)(param_2 + 0x1a) = (char)uVar6;
  wlan_operate_set_prim_ch(param_2,uVar6);
LAB_000dbd9c:
  MlmeUpdateTxRatesWdev(param_1,0,param_2);
  SetCommonHtVht(param_1,param_2);
  return;
}

