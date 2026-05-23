// module: mt7915.ko
// function: hqa_dbdc_continuous_tx @ 0x24b6c0
// size: 452 bytes
//

undefined4 hqa_dbdc_continuous_tx(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int local_40;
  int local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_40 = param_2 + 0xc;
  FUN_002474f4(1,4,&local_40,&local_3c);
  FUN_002474f4(1,4,&local_40,&local_38);
  FUN_002474f4(1,4,&local_40,&local_34);
  FUN_002474f4(1,4,&local_40,&local_30);
  FUN_002474f4(1,4,&local_40,&local_2c);
  FUN_002474f4(1,4,&local_40,&local_28);
  FUN_002474f4(1,4,&local_40,&local_24);
  FUN_002474f4(1,4,&local_40,&local_20);
  FUN_002474f4(1,4,&local_40,&local_1c);
  iVar2 = local_3c * 0xd18 + param_1;
  *(char *)(param_1 + 0x4cc) = (char)local_3c;
  *(undefined4 *)(iVar2 + 0x1184) = local_38;
  *(undefined4 *)(iVar2 + 0x11a4) = local_34;
  *(char *)(iVar2 + 0x1135) = (char)local_30;
  *(char *)(iVar2 + 0x1136) = (char)local_2c;
  *(char *)(iVar2 + 0x1132) = (char)local_28;
  *(undefined4 *)(iVar2 + 0x11a8) = local_24;
  *(char *)(iVar2 + 0x1130) = (char)local_20;
  *(undefined4 *)(iVar2 + 0x11ac) = local_1c;
  uVar1 = mt_serv_dbdc_continuous_tx(param_1);
  printk("%s: param band_idx=%u, tx_tone_en=%u, ant_mask=0x%x\n","hqa_dbdc_continuous_tx",local_3c,
         local_38,local_34);
  printk("%s: param phy_mode=%u, bw=%u, pri_ch=%u\n","hqa_dbdc_continuous_tx",local_30,local_2c,
         local_28);
  printk("%s: param rate=%u, central_ch=%u, tx_fd_mode=%u\n","hqa_dbdc_continuous_tx",local_24,
         local_20,local_1c);
  FUN_00246b90(param_2,2,uVar1);
  return uVar1;
}

