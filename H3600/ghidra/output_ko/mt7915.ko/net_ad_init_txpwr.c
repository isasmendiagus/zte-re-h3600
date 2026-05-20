// module: mt7915.ko
// function: net_ad_init_txpwr @ 0x25cd90
// size: 108 bytes
//

int net_ad_init_txpwr(undefined4 param_1,int param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  
  if (1 < param_3) {
    return 0x608;
  }
  iVar1 = net_ad_set_txpwr_sku(param_1,*(undefined1 *)(param_2 + 0xc9c),param_3,param_4,param_4);
  if ((iVar1 == 0) &&
     (iVar1 = net_ad_set_txpwr_backoff(param_1,*(undefined1 *)(param_2 + 0xc9e),param_3), iVar1 == 0
     )) {
    return 0;
  }
  printk("%s: engine init tx power fail, err=0x%08x\n","net_ad_init_txpwr",iVar1);
  return iVar1;
}

