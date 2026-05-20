// module: mt7915.ko
// function: mt_serv_revert_tx @ 0x250d5c
// size: 96 bytes
//

int mt_serv_revert_tx(undefined4 *param_1)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x7d1) == '\0') {
    iVar1 = mt_engine_unsubscribe_tx
                      (*param_1,param_1 + (uint)*(byte *)(param_1 + 0x133) * 0x346 + 0x138);
    if (iVar1 != 0) {
      printk("%s: err=0x%08x\n","mt_serv_revert_tx",iVar1);
    }
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}

