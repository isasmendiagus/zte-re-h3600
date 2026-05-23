// module: mt7915.ko
// function: mt_serv_stop_tx @ 0x250ecc
// size: 120 bytes
//

int mt_serv_stop_tx(undefined4 *param_1)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x7d1) == '\0') {
    iVar1 = mt_engine_stop_tx(*param_1,param_1 + (uint)*(byte *)(param_1 + 0x133) * 0x346 + 0x138,
                              param_1[0x7c4]);
  }
  else {
    iVar1 = (**(code **)(param_1[0x7c4] + 0x6c))(*param_1,(uint)*(byte *)(param_1 + 0x133));
  }
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_stop_tx",iVar1);
  }
  return iVar1;
}

