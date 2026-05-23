// module: mt7915.ko
// function: hqa_set_ibf_value_ext @ 0x24ec20
// size: 1404 bytes
//

/* WARNING: Type propagation algorithm not settling */

int hqa_set_ibf_value_ext(int param_1,int param_2)

{
  int iVar1;
  char *__format;
  uint uVar2;
  int local_50 [3];
  char *local_44;
  uint local_40;
  int local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24 [2];
  
  uVar2 = (uint)*(byte *)(param_1 + 0x4cc);
  local_50[0] = param_2 + 0xc;
  local_50[1] = 0;
  local_50[2] = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24[0] = 0;
  printk("%s: Band index = %d\n","hqa_set_ibf_value_ext",uVar2);
  iVar1 = sys_ad_alloc_mem(&local_44,0x200);
  if (iVar1 == 0) {
    printk("%s: cmd ptr = %p\n","hqa_set_ibf_value_ext",&local_44);
    sys_ad_zero_mem(local_44,0x200);
    FUN_002474f4(1,4,local_50,local_50 + 1);
    FUN_002474f4(1,4,local_50,local_50 + 2);
    FUN_002474f4(1,4,local_50,&local_40);
    FUN_002474f4(1,4,local_50,&local_3c);
    FUN_002474f4(1,4,local_50,&local_38);
    FUN_002474f4(1,4,local_50,&local_34);
    FUN_002474f4(1,4,local_50,&local_30);
    FUN_002474f4(1,4,local_50,&local_2c);
    FUN_002474f4(1,4,local_50,&local_28);
    FUN_002474f4(1,4,local_50,local_24);
    switch(local_50[2]) {
    case 1:
      sprintf(local_44,"%d",local_40 & 0xff);
      mt_agent_set_txbf_dut_init_proc(param_1,local_44);
      break;
    case 2:
      if (local_3c == 1) {
        __format = "%d:1";
      }
      else {
        __format = "%d";
      }
      sprintf(local_44,__format,local_40 & 0xff);
      mt_agent_set_channel(param_1,local_44);
      break;
    case 3:
      *(undefined1 *)(uVar2 * 0xd18 + param_1 + 0x1138) = (undefined1)local_40;
      break;
    case 4:
      sprintf(local_44,"%d",local_40 & 0xff);
      mt_agent_set_pwr(param_1,local_44);
      break;
    case 5:
      sprintf(local_44,"%d",local_40 & 0xff);
      mt_agent_set_txant(param_1,local_44);
      break;
    case 6:
      mt_serv_stop_tx(param_1);
      mt_serv_start_rx(param_1);
      break;
    case 7:
      sprintf(local_44,"%d",local_40 & 0xff);
      mt_agent_set_rxant(param_1,local_44);
      break;
    case 8:
      sprintf(local_44,"%d",local_40 & 0xff);
      mt_agent_set_txbf_lna_gain(param_1,local_44);
      break;
    case 9:
      sprintf(local_44,"%02x:%02x:%02x:%02x:%02x",local_40,local_3c,local_38,local_34,local_30);
      iVar1 = mt_agent_set_ibf_phase_comp(param_1,local_44);
      if (iVar1 != 0) {
        printk(" ATE_IBF_PHASE_COMP is failed!!\n");
      }
      break;
    case 10:
      local_38 = 0;
      sprintf(local_44,"%02x:%02x:%02x:%02x",local_40,local_3c,0,local_34);
      iVar1 = mt_agent_set_tx_pkt_with_ibf(param_1,local_44);
      if (iVar1 != 0) {
        printk(" ATE_IBF_TX is failed!!\n");
      }
      break;
    case 0xb:
      sprintf(local_44,"%02x:%02x:%02x",local_40,local_3c,local_38);
      iVar1 = mt_agent_set_ibf_profile_update(param_1,local_44);
      if (iVar1 == 0) {
        sys_ad_zero_mem(local_44,0x200);
        builtin_strncpy(local_44,"01:00:01:00:01",0xf);
        iVar1 = mt_agent_set_txbf_tx_apply(param_1,local_44);
        if (iVar1 != 0) {
          printk(" IBF flag setting in WTBL is failed!!\n");
        }
      }
      else {
        printk(" ATE_IBF_PROF_UPDATE is failed!!\n");
      }
      break;
    case 0xc:
      sprintf(local_44,"%02x:%02x:%02x",local_40,local_3c,local_38);
      iVar1 = mt_agent_set_ebf_profile_update(param_1,local_44);
      if (iVar1 != 0) {
        printk(" ATE_EBF_PROF_UPDATE is failed!!\n");
      }
      break;
    case 0xd:
      iVar1 = uVar2 * 0xd18 + param_1;
      local_30 = 0;
      *(uint *)(iVar1 + 0x4e0) = *(uint *)(iVar1 + 0x4e0) | 0x400;
      sprintf(local_44,"%02x:%02x:%02x:%02x:%02x",local_40,local_3c,local_38,local_34,0);
      iVar1 = mt_agent_set_ibf_inst_cal(param_1,local_44);
      if (iVar1 != 0) {
        printk(" ATE_IBF_GD_CAL is failed!!\n");
      }
      break;
    case 0xe:
      iVar1 = uVar2 * 0xd18 + param_1;
      local_34 = 4;
      *(uint *)(iVar1 + 0x4e0) = *(uint *)(iVar1 + 0x4e0) | 0x400;
      local_30 = 1;
      sprintf(local_44,"%02x:%02x:%02x:%02x:%02x",local_40,local_3c,local_38,4,1);
      iVar1 = mt_agent_set_ibf_inst_cal(param_1,local_44);
      if (iVar1 != 0) {
        printk(" ATE_IBF_INST_VERIFY is failed!!\n");
      }
      break;
    case 0x10:
      sprintf(local_44,"%02x:%02x:%02x",local_40,local_3c,local_38);
      iVar1 = mt_agent_set_ibf_phase_cal_e2p_update(param_1,local_44);
      if (iVar1 != 0) {
        printk(" ATE_IBF_PHASE_E2P_UPDATE is failed!!\n");
      }
    }
  }
  else {
    printk("CMD can\'t be created!!\n");
  }
  sys_ad_move_mem((void *)(param_2 + 0xe),local_50 + 1,4);
  FUN_00246b90(param_2,6,iVar1);
  printk("%s: End of hqa_set_ibf_value_ext()!!\n","hqa_set_ibf_value_ext");
  if (local_44 != (char *)0x0) {
    sys_ad_free_mem();
  }
  return iVar1;
}

