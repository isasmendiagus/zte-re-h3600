// module: mt7915.ko
// function: chip_get_sta_tx_cnt @ 0x190c58
// size: 56 bytes
//

undefined4 chip_get_sta_tx_cnt(undefined4 param_1,undefined2 param_2,short param_3)

{
  undefined4 local_c [2];
  
  halWtblReadRaw(param_1,param_2,0,param_3 + 0x10,1,local_c);
  return local_c[0];
}

