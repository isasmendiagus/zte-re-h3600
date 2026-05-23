// module: mt7915.ko
// function: WscGetRegDataPIN @ 0x1e6c9c
// size: 312 bytes
//

void WscGetRegDataPIN(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 local_26;
  undefined1 local_22;
  char local_21 [9];
  
  if (*(int *)(param_3 + 4) - 2U < 2) {
    param_2 = 0;
  }
  *(undefined4 *)(param_3 + 0x14) = param_2;
  local_21[0] = '\0';
  local_21[1] = '\0';
  local_21[2] = '\0';
  local_21[3] = '\0';
  local_21[4] = '\0';
  local_21[5] = '\0';
  local_21[6] = '\0';
  local_21[7] = '\0';
  local_21[8] = '\0';
  __memzero(param_3 + 0x1ae4,8);
  if (*(int *)(param_3 + 0x14) == 0) {
    local_21[0] = '0';
    local_21[1] = '0';
    local_21[2] = '0';
    local_21[3] = '0';
    local_21[4] = '0';
    local_21[5] = '0';
    local_21[6] = '0';
    local_21[7] = '0';
    local_21[8] = '\0';
    builtin_strncpy((char *)(param_3 + 0x1ae4),"0000",4);
    builtin_strncpy((char *)(param_3 + 0x1ae8),"0000",4);
    *(undefined1 *)(param_3 + 0x1aec) = 8;
  }
  else if (*(char *)(param_3 + 0x18) == '\x04') {
    local_26 = 0;
    local_22 = 0;
    snprintf((char *)&local_26,5,"%04u");
    *(undefined4 *)(param_3 + 0x1ae4) = local_26;
    *(undefined1 *)(param_3 + 0x1aec) = 4;
  }
  else {
    snprintf(local_21,9,"%08u");
    *(undefined4 *)(param_3 + 0x1ae4) = local_21._0_4_;
    *(undefined4 *)(param_3 + 0x1ae8) = local_21._4_4_;
    *(undefined1 *)(param_3 + 0x1aec) = 8;
  }
  hex_dump("WscGetRegDataPIN - PIN",param_3 + 0x1ae4,8);
  return;
}

