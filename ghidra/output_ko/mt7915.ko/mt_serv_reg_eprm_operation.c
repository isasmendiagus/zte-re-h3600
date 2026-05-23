// module: mt7915.ko
// function: mt_serv_reg_eprm_operation @ 0x2522d0
// size: 600 bytes
//

int mt_serv_reg_eprm_operation(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  
  switch(param_2) {
  case 0:
    iVar1 = net_ad_read_mac_bbp_reg(*param_1,param_1 + 0x7c5);
    break;
  case 1:
    if (*(char *)(param_1 + 0x7d1) == '\0') {
      iVar1 = net_ad_write_mac_bbp_reg(*param_1,param_1 + 0x7c5);
    }
    else {
      iVar1 = (**(code **)(param_1[0x7c4] + 0xec))(*param_1,param_1 + 0x7c5);
    }
    break;
  case 2:
    if (*(char *)(param_1 + 0x7d1) == '\0') {
      iVar1 = net_ad_read_bulk_mac_bbp_reg(*param_1,param_1 + 0x138,param_1 + 0x7c5);
    }
    else {
      iVar1 = (**(code **)(param_1[0x7c4] + 0xf0))(*param_1,param_1 + 0x7c5);
    }
    break;
  case 3:
    if (*(char *)(param_1 + 0x7d1) == '\0') {
      iVar1 = net_ad_read_bulk_rf_reg(*param_1,param_1 + 0x7c5);
    }
    else {
      iVar1 = (**(code **)(param_1[0x7c4] + 0xf4))(*param_1,param_1 + 0x7c5);
    }
    break;
  case 4:
    if (*(char *)(param_1 + 0x7d1) == '\0') {
      iVar1 = net_ad_write_bulk_rf_reg(*param_1,param_1 + 0x7c5);
    }
    else {
      iVar1 = (**(code **)(param_1[0x7c4] + 0xf8))(*param_1,param_1 + 0x7c5);
    }
    break;
  case 5:
    net_ad_read_ca53_reg(param_1 + 0x7c5);
    return 0;
  case 6:
    net_ad_write_ca53_reg(param_1 + 0x7c5);
    return 0;
  default:
    return 0x204;
  case 10:
    iVar1 = net_ad_read_write_eeprom(*param_1,param_1 + 0x7c9,1);
    break;
  case 0xb:
    iVar1 = net_ad_read_write_eeprom(*param_1,param_1 + 0x7c9,0);
    break;
  case 0xc:
    if (*(char *)(param_1 + 0x7d1) == '\0') {
      iVar1 = net_ad_read_write_bulk_eeprom(*param_1,param_1 + 0x7c9,1);
    }
    else {
      iVar1 = (**(code **)(param_1[0x7c4] + 0xfc))(*param_1,param_1 + 0x7c9);
    }
    break;
  case 0xd:
    iVar1 = net_ad_read_write_bulk_eeprom(*param_1,param_1 + 0x7c9,0);
    break;
  case 0xe:
    iVar1 = net_ad_get_free_efuse_block(*param_1,param_1 + 0x7c9);
  }
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_reg_eprm_operation",iVar1);
    return iVar1;
  }
  return 0;
}

