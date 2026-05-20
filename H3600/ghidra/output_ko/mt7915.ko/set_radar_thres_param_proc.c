// module: mt7915.ko
// function: set_radar_thres_param_proc @ 0x101684
// size: 828 bytes
//

undefined4 set_radar_thres_param_proc(int param_1,char *param_2)

{
  int iVar1;
  undefined1 local_a0;
  undefined1 local_9c;
  undefined1 local_98;
  uint local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
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
  
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_88 = 0;
  local_84 = 0;
  local_80 = 0;
  local_7c = 0;
  local_78 = 0;
  local_74 = 0;
  local_70 = 0;
  local_6c = 0;
  local_68 = 0;
  local_64 = 0;
  local_60 = 0;
  local_5c = 0;
  local_58 = 0;
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  if (param_2 != (char *)0x0) {
    iVar1 = sscanf(param_2,"%u-%u-%u-%u-%u-%u-%u-%u-%u-%u-%u-%u-%u-%u-%u-%u",&local_88,&local_84,
                   &local_80,&local_7c,&local_78,&local_74,&local_70,&local_6c,&local_54,&local_50,
                   &local_68,&local_64,&local_60,&local_5c,&local_58,&local_4c);
    if (iVar1 == 0x10) {
      if (-1 < DebugLevel) {
        printk("%s():RadarType = %d\n RT_ENB = %d\n RT_STGR = %d\n RT_CRPN_MIN = %d\n RT_CRPN_MAX = %d\n RT_CRPR_MIN = %d\n RT_PW_MIN = %d\n RT_PW_MAX =%d\n RT_PRI_MIN = %d\n RT_PRI_MAX = %d\n RT_CRBN_MIN = %d\n RT_CRBN_MAX = %d\nRT_STGPN_MIN = %d\n RT_STGPN_MAX = %d\n RT_STGPR_MIN = %d\nRT_STGPRID_MIN = %d\n"
               ,"set_radar_thres_param_proc",local_88,local_84,local_80,local_7c,local_78,local_74,
               local_70,local_6c,local_54,local_50,local_68,local_64,local_60,local_5c,local_58,
               local_4c);
      }
      __memzero(&local_48,0x20);
      local_44 = CONCAT13((undefined1)local_80,CONCAT12((undefined1)local_84,(short)local_88));
      local_40 = CONCAT13((undefined1)local_70,
                          CONCAT12((undefined1)local_74,
                                   CONCAT11((undefined1)local_78,(undefined1)local_7c)));
      local_3c = local_54;
      local_38 = local_50;
      local_a0 = (undefined1)local_64;
      local_2c = local_4c;
      local_9c = (undefined1)local_60;
      local_34 = CONCAT13(local_9c,CONCAT12(local_a0,CONCAT11((undefined1)local_68,
                                                              (undefined1)local_6c)));
      local_98 = (undefined1)local_5c;
      local_30 = CONCAT31(CONCAT21(local_30._2_2_,(undefined1)local_58),local_98);
      if (local_88 < 0x10) {
        iVar1 = param_1 + local_88 * 0x1c;
        if (iVar1 != -0x795468) {
          *(undefined1 *)(iVar1 + 0x795469) = (undefined1)local_84;
          *(undefined1 *)(iVar1 + 0x79546a) = (undefined1)local_80;
          *(undefined1 *)(iVar1 + 0x79546b) = (undefined1)local_7c;
          *(undefined1 *)(iVar1 + 0x79546c) = (undefined1)local_78;
          *(undefined1 *)(iVar1 + 0x79546d) = (undefined1)local_74;
          *(undefined1 *)(iVar1 + 0x79546e) = (undefined1)local_70;
          *(undefined1 *)(iVar1 + 0x79546f) = (undefined1)local_6c;
          *(undefined4 *)(iVar1 + 0x795470) = local_54;
          *(undefined4 *)(iVar1 + 0x795474) = local_50;
          *(undefined1 *)(iVar1 + 0x79547c) = (undefined1)local_58;
          *(undefined1 *)(iVar1 + 0x795478) = (undefined1)local_68;
          *(undefined1 *)(iVar1 + 0x795479) = local_a0;
          *(undefined1 *)(iVar1 + 0x79547a) = local_9c;
          *(undefined1 *)(iVar1 + 0x79547b) = local_98;
          *(undefined4 *)(iVar1 + 0x795480) = local_4c;
        }
      }
      mt_cmd_set_radar_thres_param(param_1,&local_48);
      return 1;
    }
    if (-1 < DebugLevel) {
      printk(
            "Format Error! Please enter in the following format\nRadarType-RT_ENB-RT_STGR-RT_CRPN_MIN-RT_CRPN_MAX-RT_CRPR_MIN-RT_PW_MIN-RT_PW_MAX-RT_PRI_MIN-RT_PRI_MAX-RT_CRBN_MIN-RT_CRBN_MAX-RT_STGPN_MIN-RT_STGPN_MAX-RT_STGPR_MIN-RT_STGPRID_MIN\n"
            );
    }
  }
  return 1;
}

