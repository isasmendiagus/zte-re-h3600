// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_siwessid @ 0x62914
// size: 204 bytes
//

undefined4 RtmpIoctl_rt_ioctl_siwessid(undefined4 param_1,char *param_2)

{
  int iVar1;
  void *local_14 [2];
  
  if (*param_2 == '\0') {
    iVar1 = Set_SSID_Proc(param_1,&_LC93);
    if (iVar1 == 0) {
      param_2[0xc] = '0';
      param_2[0xd] = 'u';
      param_2[0xe] = '\0';
      param_2[0xf] = '\0';
    }
    return 0;
  }
  local_14[0] = (void *)0x0;
  os_alloc_mem(0,local_14,0x21);
  if (local_14[0] == (void *)0x0) {
    param_2[0xc] = '5';
    param_2[0xd] = 'u';
    param_2[0xe] = '\0';
    param_2[0xf] = '\0';
    return 0;
  }
  __memzero(local_14[0],0x21);
  memmove(local_14[0],*(void **)(param_2 + 8),*(size_t *)(param_2 + 4));
  iVar1 = Set_SSID_Proc(param_1,local_14[0]);
  if (iVar1 != 0) {
    os_free_mem(local_14[0]);
    return 0;
  }
  os_free_mem(local_14[0]);
  param_2[0xc] = '0';
  param_2[0xd] = 'u';
  param_2[0xe] = '\0';
  param_2[0xf] = '\0';
  return 0;
}

