// module: mt7915.ko
// function: RTMPSuspendMsduTransmission @ 0x128c64
// size: 92 bytes
//

void RTMPSuspendMsduTransmission(int param_1,int param_2)

{
  if (2 < DebugLevel) {
    printk("SCANNING, suspend MSDU transmission ...\n");
  }
  bbp_get_agc(param_1,"rtmp_read_dot11v_mbssid_cfg_from_file" + param_1 + 0x1b,1);
  OS_SET_BIT(1,param_2 + 0x88c);
  return;
}

