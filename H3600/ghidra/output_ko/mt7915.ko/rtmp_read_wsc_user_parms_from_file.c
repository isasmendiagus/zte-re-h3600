// module: mt7915.ko
// function: rtmp_read_wsc_user_parms_from_file @ 0xf06a0
// size: 140 bytes
//

void rtmp_read_wsc_user_parms_from_file(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  
  pbVar3 = (byte *)(param_1 + 0x3678c7);
  iVar2 = 0;
  while( true ) {
    iVar1 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    if (iVar1 <= iVar2) break;
    pbVar3 = pbVar3 + 1;
    rtmp_read_wsc_user_parms
              ("4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
               + (uint)*pbVar3 * 0x5834 + param_1 + 0x2b,param_2,param_3);
    iVar2 = iVar2 + 1;
  }
  rtmp_read_wsc_user_parms(&DAT_0036ee3c + param_1,param_2,param_3);
  rtmp_read_wsc_user_parms(&DAT_0036ee3c + param_1,param_2,param_3);
  return;
}

