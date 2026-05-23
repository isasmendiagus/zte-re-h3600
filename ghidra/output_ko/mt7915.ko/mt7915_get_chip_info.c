// module: mt7915.ko
// function: mt7915_get_chip_info @ 0x187f54
// size: 120 bytes
//

undefined4 mt7915_get_chip_info(int param_1)

{
  undefined4 local_14 [2];
  
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x70010204,local_14);
  *(undefined4 *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0x10) = local_14[0];
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x70010208,local_14);
  *(undefined4 *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0x14) = local_14[0];
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x70010200,local_14);
  *(undefined4 *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) = local_14[0];
  return 1;
}

