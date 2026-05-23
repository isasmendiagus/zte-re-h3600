// module: mt7915.ko
// function: chip_get_sta_addr @ 0x190bf4
// size: 52 bytes
//

undefined4 chip_get_sta_addr(undefined4 param_1,undefined2 param_2)

{
  undefined4 local_c [2];
  
  halWtblReadRaw(param_1,param_2,0,0,1,local_c);
  return local_c[0];
}

