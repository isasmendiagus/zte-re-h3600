// module: plat-zxylzb_9128S.ko
// function: brg_cal_mac_hash @ 0x16900
// size: 24 bytes
//

uint brg_cal_mac_hash(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  
  uVar1 = crc_16(param_1,6,0,param_4,param_4);
  return uVar1 & 0x3ff;
}

