// module: mt7915.ko
// function: antenna_default_reset @ 0x17d38c
// size: 528 bytes
//

void antenna_default_reset(int param_1,byte *param_2)

{
  char cVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  ushort local_22 [3];
  
  iVar3 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  cVar1 = *(char *)(iVar3 + 0x6d);
  if (-1 < DebugLevel) {
    printk("%s() todo\n","antenna_default_reset");
  }
  param_2[0] = 0;
  param_2[1] = 0;
  "rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x1e] = '#';
  chip_eeprom_read16(param_1,400,local_22);
  uVar5 = (uint)local_22[0];
  uVar4 = (uVar5 << 0x1a) >> 0x1d;
  *param_2 = (byte)((uVar5 & 7) << 4) | (byte)((uVar5 << 0x1a) >> 0x1d);
  uVar6 = uVar4;
  if (4 < (uVar5 & 7) || (local_22[0] & 7) == 0) {
    uVar6 = uVar4 | 0x40;
    *param_2 = (byte)uVar6;
  }
  if (4 < uVar4 || (uVar6 & 0xf) == 0) {
    *param_2 = *param_2 & 0xf0 | 4;
  }
  if (-1 < DebugLevel) {
    printk("%s() value = 0x%x, TxPath = %d, RxPath = %d\n","antenna_default_reset",uVar5,
           *param_2 >> 4,*param_2 & 0xf);
  }
  if (cVar1 == '\x04') {
    chip_eeprom_read16(param_1,0x193,local_22);
    uVar6 = (uint)local_22[0];
    uVar2 = local_22[0] & 0xff;
    "SetPartProfileParameters"[param_1 + 0x1a] = (char)(uVar6 & 3);
    "SetPartProfileParameters"[param_1 + 0x1b] = (byte)((uVar6 << 0x1c) >> 0x1e);
    if (1 < ((uVar6 << 0x1c) >> 0x1e) - 1) {
      "SetPartProfileParameters"[param_1 + 0x1b] = '\x02';
    }
    "rtmp_read_vow_parms_from_file"[param_1 + 1] = (byte)local_22[0] >> 6;
    if (1 < (uVar6 & 3) - 1) {
      "SetPartProfileParameters"[param_1 + 0x1a] = '\x02';
    }
    "rtmp_read_vow_parms_from_file"[param_1] = (byte)((uVar6 << 0x1a) >> 0x1e);
    if (1 < ((uVar6 << 0x18) >> 0x1e) - 1) {
      "rtmp_read_vow_parms_from_file"[param_1 + 1] = '\x02';
    }
    local_22[0] = uVar2;
    if (1 < ((uVar6 << 0x1a) >> 0x1e) - 1) {
      "rtmp_read_vow_parms_from_file"[param_1] = '\x02';
    }
  }
  else {
    "SetPartProfileParameters"[param_1 + 0x1b] = '\x01';
    "SetPartProfileParameters"[param_1 + 0x1a] = '\x01';
    "rtmp_read_vow_parms_from_file"[param_1 + 1] = '\x01';
    "rtmp_read_vow_parms_from_file"[param_1] = '\x01';
  }
  if ((3 < DebugLevel) &&
     (printk("%s(): DBDC BAND0 TxPath = %d, RxPath = %d\n","antenna_default_reset",
             "SetPartProfileParameters"[param_1 + 0x1a],"SetPartProfileParameters"[param_1 + 0x1b]),
     3 < DebugLevel)) {
    printk("%s(): DBDC BAND1 TxPath = %d, RxPath = %d\n","antenna_default_reset",
           "rtmp_read_vow_parms_from_file"[param_1],"rtmp_read_vow_parms_from_file"[param_1 + 1]);
  }
  return;
}

