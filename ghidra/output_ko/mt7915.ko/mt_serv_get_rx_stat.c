// module: mt7915.ko
// function: mt_serv_get_rx_stat @ 0x251d40
// size: 376 bytes
//

int mt_serv_get_rx_stat(int *param_1,int param_2,uint param_3,undefined4 param_4,void *param_5)

{
  int iVar1;
  
  iVar1 = param_1[0x7c4];
  if (*(char *)(*param_1 + 0x34) == '\0' && param_2 != 0) {
    printk("%s: invalid band index for non-dbdc mode.\n","mt_serv_get_rx_stat");
    return 0;
  }
  switch(param_4) {
  case 0:
    if (1 < param_3) {
      return 0;
    }
    iVar1 = (**(code **)(iVar1 + 0x158))();
    sys_ad_move_mem(param_5,param_1 + param_3 * 0xe + param_2 * 0x6b + 0x5b,0x38);
    break;
  case 1:
    if (3 < param_3) {
      return 0;
    }
    iVar1 = (**(code **)(iVar1 + 0x15c))();
    sys_ad_move_mem(param_5,param_1 + param_3 * 6 + param_2 * 0x6b + 0x77,0x18);
    break;
  case 2:
    if (0xf < param_3) {
      return 0;
    }
    iVar1 = (**(code **)(iVar1 + 0x160))();
    sys_ad_move_mem(param_5,param_1 + param_3 * 3 + param_2 * 0x6b + 0x8f,0xc);
    break;
  case 3:
    iVar1 = (**(code **)(iVar1 + 0x164))();
    sys_ad_move_mem(param_5,param_1 + param_2 * 0x6b + 0xbf,0x1c);
    break;
  default:
    return 0;
  }
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_get_rx_stat",iVar1);
  }
  return iVar1;
}

