// module: mt7915.ko
// function: txcmdsu_dbg_init @ 0x28f390
// size: 44 bytes
//

void txcmdsu_dbg_init(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  dbg_txcmd_feature_register(param_1,&_LANCHOR1);
  printk(&_LC107,"TXCMDSU","txcmdsu_dbg_init",param_4);
  return;
}

