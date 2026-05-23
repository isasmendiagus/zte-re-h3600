// module: mt7915.ko
// function: ConvertToRssi @ 0x103210
// size: 124 bytes
//

int ConvertToRssi(int param_1,int param_2,int param_3)

{
  char cVar1;
  char cVar2;
  char local_14 [4];
  
  local_14[0] = '\0';
  local_14[1] = '\0';
  local_14[2] = '\0';
  local_14[3] = '\0';
  if ((param_3 < (int)((byte)"SetPartProfileParameters"[param_1 + 0x18] & 0xf)) &&
     (cVar1 = *(char *)(param_2 + param_3), cVar1 != '\0')) {
    cVar2 = "Get_RBIST_IQ_Data_Proc"[param_1 + 4];
    AsicFeLossGet(param_1,"rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x20],local_14);
    return (int)(char)((cVar1 + local_14[param_3]) - cVar2);
  }
  return -99;
}

