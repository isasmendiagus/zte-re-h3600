// module: mt7915.ko
// function: mt_serv_get_tx_info @ 0x25295c
// size: 76 bytes
//

int mt_serv_get_tx_info(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(param_1[0x7c4] + 0x28))(*param_1,param_1 + 0x138,param_1 + 0x47e);
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_get_tx_info",iVar1);
  }
  return iVar1;
}

