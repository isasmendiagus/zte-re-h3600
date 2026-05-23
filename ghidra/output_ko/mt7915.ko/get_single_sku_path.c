// module: mt7915.ko
// function: get_single_sku_path @ 0x14ee7c
// size: 24 bytes
//

char * get_single_sku_path(int param_1)

{
  char *pcVar1;
  
  pcVar1 = "Get_System_CapNode_Info" + param_1 + 4;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  return s__etc_wireless_mediatek_mt7615e_s_0033aaf4;
}

