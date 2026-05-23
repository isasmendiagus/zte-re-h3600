// module: mt7915.ko
// function: mt_serv_get_icap_max_data_len @ 0x2518c8
// size: 76 bytes
//

int mt_serv_get_icap_max_data_len(undefined4 *param_1)

{
  int iVar1;
  
  if (*(code **)(param_1[0x7c4] + 0xbc) == (code *)0x0) {
    iVar1 = 0x205;
  }
  else {
    iVar1 = (**(code **)(param_1[0x7c4] + 0xbc))(*param_1);
    if (iVar1 == 0) {
      return 0;
    }
  }
  printk("%s: err = 0x%08x\n","mt_serv_get_icap_max_data_len",iVar1);
  return iVar1;
}

