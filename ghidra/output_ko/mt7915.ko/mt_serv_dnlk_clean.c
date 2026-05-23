// module: mt7915.ko
// function: mt_serv_dnlk_clean @ 0x252a48
// size: 64 bytes
//

int mt_serv_dnlk_clean(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(param_1[0x7c4] + 0x180))(*param_1);
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_dnlk_clean",iVar1);
  }
  return iVar1;
}

