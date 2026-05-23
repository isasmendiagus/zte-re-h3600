// module: mt7915.ko
// function: os_file_open @ 0x142928
// size: 156 bytes
//

uint * os_file_open(uint *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint local_30;
  uint uStack_2c;
  uint uStack_28;
  uint uStack_24;
  uint local_20;
  uint local_1c;
  
  os_zero_mem(&local_30,0x18);
  local_30 = RtmpOSFileOpen(param_2,param_3,param_4);
  if ((local_30 == 0) || (0xfffff000 < local_30)) {
    local_20 = 1;
  }
  else {
    local_20 = 0;
    local_1c = *(uint *)(*(int *)(*(int *)(local_30 + 0xc) + 0x28) + 0x28);
    RtmpOSFSInfoChange(&uStack_2c,1);
  }
  *param_1 = local_30;
  param_1[1] = uStack_2c;
  param_1[2] = uStack_28;
  param_1[3] = uStack_24;
  param_1[4] = local_20;
  param_1[5] = local_1c;
  return param_1;
}

