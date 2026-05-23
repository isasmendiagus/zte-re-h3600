// module: mt7915.ko
// function: hqa_dbdc_tx_tone @ 0x24b888
// size: 508 bytes
//

undefined4 hqa_dbdc_tx_tone(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int local_54;
  int local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c [2];
  
  local_54 = param_2 + 0xc;
  FUN_002474f4(1,4,&local_54,&local_50);
  FUN_002474f4(1,4,&local_54,&local_4c);
  FUN_002474f4(1,4,&local_54,&local_48);
  FUN_002474f4(1,4,&local_54,&local_44);
  FUN_002474f4(1,4,&local_54,&local_40);
  FUN_002474f4(1,4,&local_54,&local_3c);
  FUN_002474f4(1,4,&local_54,&local_38);
  FUN_002474f4(1,4,&local_54,&local_34);
  FUN_002474f4(1,4,&local_54,&local_30);
  FUN_002474f4(1,4,&local_54,local_2c);
  iVar2 = local_50 * 0xd18 + param_1;
  *(char *)(param_1 + 0x4cc) = (char)local_50;
  *(undefined4 *)(iVar2 + 0x1184) = local_4c;
  *(undefined4 *)(iVar2 + 0x1188) = local_48;
  *(undefined4 *)(iVar2 + 0x118c) = local_44;
  *(undefined4 *)(iVar2 + 0x1190) = local_40;
  *(undefined4 *)(iVar2 + 0x1194) = local_3c;
  *(undefined4 *)(iVar2 + 0x1198) = local_38;
  *(char *)(iVar2 + 0x1131) = (char)local_34;
  *(undefined4 *)(iVar2 + 0x119c) = local_30;
  *(undefined4 *)(iVar2 + 0x11a0) = local_2c[0];
  mt_serv_dbdc_tx_tone(param_1);
  uVar1 = mt_serv_dbdc_tx_tone_pwr(param_1);
  printk("%s: band_idx=%u, tx_tone_en=%u, ant_idx=0x%x\n","hqa_dbdc_tx_tone",local_50,local_4c,
         local_48);
  printk("%s: tone_type=%u, tone_freq=%u, dc_offset_I=0x%x\n","hqa_dbdc_tx_tone",local_44,local_40,
         local_3c);
  printk("%s: dc_offset_Q=%u, band=%u, rf_pwr=0x%x, digi_pwr=0x%x\n","hqa_dbdc_tx_tone",local_38,
         local_34,local_30,local_2c[0]);
  FUN_00246b90(param_2,2,uVar1);
  return uVar1;
}

