// module: mt7915.ko
// function: mt_serv_set_tx_path @ 0x250c44
// size: 84 bytes
//

int mt_serv_set_tx_path(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(param_1[0x7c4] + 8))
                    (*param_1,(uint)*(byte *)(param_1 + 0x133),
                     param_1 + (uint)*(byte *)(param_1 + 0x133) * 0x346 + 0x138);
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_set_tx_path",iVar1);
  }
  return iVar1;
}

