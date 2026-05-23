// module: mt7915.ko
// function: mt_serv_submit_tx @ 0x250cf4
// size: 100 bytes
//

int mt_serv_submit_tx(undefined4 *param_1)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x7d1) == '\0') {
    iVar1 = mt_engine_subscribe_tx
                      (param_1[0x7c4],*param_1,
                       param_1 + (uint)*(byte *)(param_1 + 0x133) * 0x346 + 0x138);
    if (iVar1 != 0) {
      printk("%s: err=0x%04x\n","mt_serv_submit_tx",iVar1);
    }
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}

