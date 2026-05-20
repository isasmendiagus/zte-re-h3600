// module: mt7915.ko
// function: setCNNum @ 0x1553c0
// size: 244 bytes
//

undefined4 setCNNum(int param_1,int param_2)

{
  undefined4 *puVar1;
  uint local_c;
  
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) != 0x7615 &&
      (*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) != 0x7622) {
    return 1;
  }
  if (param_2 != 0) {
    puVar1 = (undefined4 *)(param_1 + 0xa789e0);
    *(undefined1 *)(param_1 + 0xa7c2ec) = 0;
    do {
      puVar1 = puVar1 + 1;
      *puVar1 = 0xffffffff;
    } while (puVar1 != (undefined4 *)(param_1 + 0xa78a08));
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x1066c,&local_c);
    local_c = local_c | 0xd0;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x1066c);
    return 1;
  }
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x1066c,&local_c);
  local_c = local_c & 0xffffff0f;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x1066c);
  return 1;
}

