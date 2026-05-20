// module: mt7915.ko
// function: mt_serv_set_low_power @ 0x252270
// size: 52 bytes
//

int mt_serv_set_low_power(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = net_ad_set_low_power(*param_1);
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_set_low_power",iVar1);
  }
  return iVar1;
}

