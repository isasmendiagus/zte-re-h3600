// module: mt7915.ko
// function: WscUUIDInit @ 0x1f29f8
// size: 752 bytes
//

void WscUUIDInit(int param_1,uint param_2,int param_3)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  uint local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  
  local_38 = (uint)(param_3 != 0);
  if (1 < (int)param_2) {
    local_38 = 0;
  }
  if (local_38 == 0) {
    local_34 = local_38;
    local_30 = local_38;
    local_2c = local_38;
    if (0 < DebugLevel) {
      printk("Generate UUID for apidx(%d)\n");
    }
    iVar2 = memcmp("IF(ra0) Set_WscPinCode_Proc::(PinCode=%d)\n" + param_1 + param_2 * 0x5834 + 4,
                   &local_38,0x10);
    if (iVar2 == 0) {
      WscGenerateUUID(param_1,"IF(ra0) Set_WscPinCode_Proc::(PinCode=%d)\n" +
                              param_1 + param_2 * 0x5834 + 4,
                      "IF(ra0) Set_WscPinCode_Proc::(PinCode=%d)\n" +
                      param_1 + param_2 * 0x5834 + 0x14,param_2,0,param_3);
    }
    WscInit(param_1,0,param_2 & 0xff);
    return;
  }
  iVar2 = param_1 + param_2 * 0x2137b0;
  __memzero(iVar2 + 0x370a91,6);
  *(undefined2 *)(&DAT_0036ee46 + iVar2) = 0x238c;
  WscGenerateUUID(param_1,s_QUEUE_INFO_00371858 + iVar2 + 8,
                  s_QUE_SIZE_PEAK_CURR_00371864 + iVar2 + 0xc,0,0,param_3);
  s_exp_main__maybe_jump_from_RST_00371a08[iVar2 + 0x15] = '\0';
  pcVar1 = s_exp_main__maybe_jump_from_RST_00371a08 + iVar2 + 0x1c;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  (s_TotalTimeForDump_0x_x____d_secs__00371a28 + iVar2)[0] = -0x80;
  (s_TotalTimeForDump_0x_x____d_secs__00371a28 + iVar2)[1] = '\0';
  if (*(int *)(s_exp_main__maybe_jump_from_RST_00371a08 + iVar2 + 0x18) != 0) {
    os_free_mem();
    pcVar1 = s_exp_main__maybe_jump_from_RST_00371a08 + iVar2 + 0x18;
    pcVar1[0] = '\0';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
  }
  os_alloc_mem(param_1,s_exp_main__maybe_jump_from_RST_00371a08 +
                       param_1 + param_2 * 0x2137b0 + 0x18,0x900);
  if (*(int *)(s_exp_main__maybe_jump_from_RST_00371a08 + param_1 + param_2 * 0x2137b0 + 0x18) != 0)
  {
    __memzero(*(int *)(s_exp_main__maybe_jump_from_RST_00371a08 +
                      param_1 + param_2 * 0x2137b0 + 0x18),0x900);
  }
  iVar3 = param_1 + param_2 * 0x2137b0;
  iVar2 = *(int *)(s_TotalTimeForDump_0x_x____d_secs__00371a28 + iVar3 + 8);
  pcVar1 = s_TotalTimeForDump_0x_x____d_secs__00371a28 + iVar3 + 4;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  if (iVar2 != 0) {
    os_free_mem();
    pcVar1 = s_TotalTimeForDump_0x_x____d_secs__00371a28 + iVar3 + 8;
    pcVar1[0] = '\0';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
  }
  os_alloc_mem(param_1,s_TotalTimeForDump_0x_x____d_secs__00371a28 +
                       param_1 + param_2 * 0x2137b0 + 8,0x900);
  if (*(int *)(s_TotalTimeForDump_0x_x____d_secs__00371a28 + param_1 + param_2 * 0x2137b0 + 8) != 0)
  {
    __memzero(*(int *)(s_TotalTimeForDump_0x_x____d_secs__00371a28 +
                      param_1 + param_2 * 0x2137b0 + 8),0x900);
  }
  iVar2 = param_1 + param_2 * 0x2137b0;
  pcVar1 = s_TotalTimeForDump_0x_x____d_secs__00371a28 + iVar2 + 0x1c;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = s_TotalTimeForDump_0x_x____d_secs__00371a28 + iVar2 + 0x18;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  s_TotalTimeForDump_0x_x____d_secs__00371a28[iVar2 + 0x20] = '\0';
  pcVar1 = s_TotalTimeForDump_0x_x____d_secs__00371a28 + iVar2 + 0x14;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  s_exp_main__maybe_jump_from_RST_00371a08[iVar2 + 0xe] = '\0';
  s_exp_main__maybe_jump_from_RST_00371a08[iVar2 + 0xd] = '\0';
  s____addtional_information_0037195c[iVar2 + 0x10] = '\x01';
  (s____addtional_information_0037195c + iVar2 + 6)[0] = '\0';
  (s____addtional_information_0037195c + iVar2 + 6)[1] = '\0';
  (s____addtional_information_0037195c + iVar2 + 4)[0] = '\0';
  (s____addtional_information_0037195c + iVar2 + 4)[1] = '\0';
  pcVar1 = s____addtional_information_0037195c + iVar2 + 8;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  s____addtional_information_0037195c[iVar2 + 0xc] = '\0';
  s____addtional_information_0037195c[iVar2 + 0x11] = '\x01';
  WscInit(param_1,1,param_2 & 0xff);
  return;
}

