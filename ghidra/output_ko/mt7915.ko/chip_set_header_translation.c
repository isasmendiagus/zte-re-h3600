// module: mt7915.ko
// function: chip_set_header_translation @ 0x190c90
// size: 100 bytes
//

void chip_set_header_translation(undefined4 param_1,undefined2 param_2,int param_3)

{
  uint local_14;
  
  halWtblReadRaw(param_1,param_2,0,4,1,&local_14);
  if (param_3 == 0) {
    local_14 = local_14 | 0x10000000;
  }
  else {
    local_14 = local_14 & 0xefffffff;
  }
  halWtblWriteRaw(param_1,param_2,0,4,local_14);
  return;
}

