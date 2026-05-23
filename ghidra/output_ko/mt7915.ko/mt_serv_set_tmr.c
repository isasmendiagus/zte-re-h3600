// module: mt7915.ko
// function: mt_serv_set_tmr @ 0x2526dc
// size: 60 bytes
//

int mt_serv_set_tmr(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = net_ad_set_tmr(*param_1,param_1 + 0x7cd);
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_set_tmr",iVar1);
  }
  return iVar1;
}

