// module: mt7915.ko
// function: Show_Channel_Proc @ 0xd5b08
// size: 88 bytes
//

undefined4 Show_Channel_Proc(int *param_1,char *param_2,size_t param_3,undefined4 param_4)

{
  char *__format;
  int iVar1;
  
  iVar1 = *param_1;
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(iVar1 + 0x3c),*(undefined4 *)(iVar1 + 0x38),iVar1,
                     param_4);
  if (iVar1 != 0) {
    if (*(byte *)(iVar1 + 0x1a) < 0xf) {
      __format = "\t2.4G Band: %d\n";
    }
    else {
      __format = "\t5G Band: %d\n";
    }
    snprintf(param_2,param_3,__format);
  }
  return 0;
}

