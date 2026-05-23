// module: mt7915.ko
// function: chip_set_hw_amsdu @ 0x190cf4
// size: 120 bytes
//

void chip_set_hw_amsdu(undefined4 param_1,undefined2 param_2,int param_3,uint param_4)

{
  uint local_1c [2];
  
  halWtblReadRaw(param_1,param_2,1,6,1,local_1c);
  if (param_4 != 0) {
    local_1c[0] = param_4 | local_1c[0] & 0xffffffc0;
  }
  local_1c[0] = local_1c[0] & 0xfffffe3f | param_3 << 6;
  halWtblWriteRaw(param_1,param_2,1,6,local_1c[0]);
  return;
}

