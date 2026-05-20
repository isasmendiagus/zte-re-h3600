// module: mt7915.ko
// function: RTMPResumeMsduTransmission @ 0x128cc0
// size: 192 bytes
//

void RTMPResumeMsduTransmission(int param_1,int param_2)

{
  int iVar1;
  undefined1 uVar2;
  char cVar3;
  int iVar4;
  
  iVar4 = *(int *)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14);
  uVar2 = hif_get_resource_idx(*(undefined4 *)(param_1 + 0xa797a0),param_2,0,0);
  if (2 < DebugLevel) {
    printk("SCAN done, resume MSDU transmission ...\n");
  }
  iVar1 = DebugLevel;
  cVar3 = "rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x1b];
  if (cVar3 == '\0') {
    "rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x1b] = '8';
    if (iVar1 < 0) {
      cVar3 = '8';
    }
    else {
      printk("RTMPResumeMsduTransmission, R66CurrentValue=0...\n",0);
      cVar3 = "rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x1b];
    }
  }
  bbp_set_agc(param_1,cVar3,0xf);
  OS_CLEAR_BIT(1,param_2 + 0x88c);
                    /* WARNING: Could not recover jumptable at 0x00128d58. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar4 + 0x3c))(param_1,uVar2);
  return;
}

