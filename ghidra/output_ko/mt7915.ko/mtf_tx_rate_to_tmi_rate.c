// module: mt7915.ko
// function: mtf_tx_rate_to_tmi_rate @ 0x19d98c
// size: 288 bytes
//

uint mtf_tx_rate_to_tmi_rate(int param_1,uint param_2,int param_3,int param_4,char param_5)

{
  uint uVar1;
  
  uVar1 = (uint)(param_4 == 1);
  switch(param_1) {
  case 0:
    if (param_5 == '\0') {
      if (param_2 < tmi_rate_map_cck_sp_size) {
        return (uint)*(byte *)((int)&tmi_rate_map_cck_sp + param_2);
      }
      return 0;
    }
    if (param_2 < tmi_rate_map_cck_lp_size) {
      return (uint)*(byte *)((int)&tmi_rate_map_cck_lp + param_2);
    }
    break;
  case 1:
    if (param_2 < tmi_rate_map_ofdm_size) {
      return *(byte *)((int)&tmi_rate_map_ofdm + param_2) | 0x40;
    }
    break;
  case 2:
  case 3:
    return param_2 | (param_3 - 1U & 7) << 10 | param_1 << 6 | uVar1 << 0xd;
  case 4:
    return param_2 | 0x100 | (param_3 - 1U & 7) << 10 | uVar1 << 0xd;
  case 5:
  case 8:
  case 9:
  case 10:
  case 0xb:
    return param_2 | (param_3 - 1U & 7) << 10 | param_1 << 6 | uVar1 << 0xd;
  default:
    if (-1 < DebugLevel) {
      printk("%s():Invalid mode(mode=%d)\n","mtf_tx_rate_to_tmi_rate",param_1,DebugLevel,param_4);
      return 0;
    }
  }
  return 0;
}

