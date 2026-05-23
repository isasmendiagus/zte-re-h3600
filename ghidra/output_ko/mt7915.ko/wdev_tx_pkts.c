// module: mt7915.ko
// function: wdev_tx_pkts @ 0xcda5c
// size: 516 bytes
//

undefined4 wdev_tx_pkts(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  uint uVar2;
  byte *pbVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  
  if (param_3 != 0) {
    piVar5 = (int *)(param_2 + -4);
    iVar4 = 0;
    do {
      piVar5 = piVar5 + 1;
      iVar6 = *piVar5;
      if (((*(uint *)(param_1 + 0xa39f84) & 0x44) == 4) &&
         (iVar1 = IsHcRadioCurStatOffByWdev(param_4), iVar1 == 0)) {
        iVar1 = IsStopingPdma(param_1 + 0xa7bf04);
        if (iVar1 == 0) {
          if (*(int *)(param_4 + 0x88c) == 0) {
            *(undefined1 *)(iVar6 + 0x2d) = *(undefined1 *)(param_4 + 0xc);
            if (*(int *)(param_4 + 0x14) == 2) {
              RTMPWakeUpWdev(param_1,param_4);
            }
            *(undefined2 *)(iVar6 + 0x42) = 0xffff;
            if (*(int *)(param_4 + 0x14) == 1) {
              pbVar3 = *(byte **)(iVar6 + 0xcc);
              uVar2 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
              if ((uVar2 & 0x400) == 0) {
                if ((*(char *)(param_4 + 0x890) == '\0') && ((*pbVar3 & 1) != 0)) {
                  a4_send_clone_pkt(param_1,*(undefined1 *)(param_4 + 0xe),iVar6);
                }
              }
              else if ((*pbVar3 & 1) != 0) {
                a4_send_clone_pkt(param_1,*(undefined1 *)(param_4 + 0xe),iVar6,0);
              }
            }
            send_data_pkt(param_1,param_4,iVar6);
          }
          else {
            *(int *)(param_1 + 0x9db88) = *(int *)(param_1 + 0x9db88) + 1;
            wlan_dbg_radio_statistics_inc(0,5);
            RTMPFreeNdisPacket(param_1,iVar6);
          }
        }
        else {
          *(int *)(param_1 + 0x9db84) = *(int *)(param_1 + 0x9db84) + 1;
          RTMPFreeNdisPacket(param_1,iVar6);
          wlan_dbg_set_last_error(0,0,0x1d3e,"wdev_tx_pkts");
        }
      }
      else {
        *(int *)(param_1 + 0x9db80) = *(int *)(param_1 + 0x9db80) + 1;
        RTMPFreeNdisPacket(param_1,iVar6);
        wlan_dbg_set_last_error(0,0,0x1d36,"wdev_tx_pkts");
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 != param_3);
    return 0;
  }
  return 0;
}

