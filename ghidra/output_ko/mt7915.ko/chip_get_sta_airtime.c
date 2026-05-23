// module: mt7915.ko
// function: chip_get_sta_airtime @ 0x190b84
// size: 112 bytes
//

undefined4 chip_get_sta_airtime(undefined4 param_1,undefined4 param_2,short param_3,int param_4)

{
  undefined4 local_c [2];
  
  if (param_4 == 0) {
    halWtblReadRaw(param_1,param_2,0,param_3 * 2 + 0x15,1,local_c);
    return local_c[0];
  }
  halWtblReadRaw(param_1,param_2,0,param_3 * 2 + 0x14,1,local_c);
  return local_c[0];
}

