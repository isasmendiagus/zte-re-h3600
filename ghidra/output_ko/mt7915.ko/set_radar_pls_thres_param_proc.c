// module: mt7915.ko
// function: set_radar_pls_thres_param_proc @ 0x1019c4
// size: 388 bytes
//

undefined4 set_radar_pls_thres_param_proc(int param_1,char *param_2)

{
  int iVar1;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  if (param_2 != (char *)0x0) {
    iVar1 = sscanf(param_2,"%d-%d-%d-%d-%d-%d-%d",&local_4c,&local_54,&local_50,&local_48,&local_44,
                   &local_40,&local_3c);
    if (iVar1 == 7) {
      if (-1 < DebugLevel) {
        printk("%s():MaxPulseWidth = %d\nMaxPulsePower = %d\nMinPulsePower = %d\nMinPRISTGR = %d\nMaxPRISTGR = %d\nMinPRICR = %d\nMaxPRICR = %d\n"
               ,"set_radar_pls_thres_param_proc",local_4c,local_54,local_50,local_48,local_44,
               local_40,local_3c);
      }
      *(undefined4 *)(param_1 + 0x79543c) = local_4c;
      *(undefined4 *)(param_1 + 0x795440) = local_54;
      *(undefined4 *)(param_1 + 0x795444) = local_50;
      *(undefined4 *)(param_1 + 0x795448) = local_48;
      *(undefined4 *)(param_1 + 0x79544c) = local_44;
      *(undefined4 *)(param_1 + 0x795450) = local_40;
      *(undefined4 *)(param_1 + 0x795454) = local_3c;
      local_34 = local_4c;
      local_30 = local_54;
      local_2c = local_50;
      local_28 = local_48;
      local_24 = local_44;
      local_20 = local_40;
      local_1c = local_3c;
      mt_cmd_set_pls_thres_param(param_1,&local_38);
      return 1;
    }
    if (-1 < DebugLevel) {
      printk(
            "Format Error! Please enter in the following format\nMaxPulseWidth-MaxPulsePower-MinPulsePower-MinPRISTGR-MaxPRISTGR-MinPRICR-MaxPRICR\n"
            );
    }
  }
  return 1;
}

