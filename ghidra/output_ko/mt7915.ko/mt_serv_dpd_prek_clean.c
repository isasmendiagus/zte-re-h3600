// module: mt7915.ko
// function: mt_serv_dpd_prek_clean @ 0x2511d0
// size: 68 bytes
//

int mt_serv_dpd_prek_clean(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(param_1[0x7c4] + 400))(*param_1,0);
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_dpd_prek_clean",iVar1);
  }
  return iVar1;
}

