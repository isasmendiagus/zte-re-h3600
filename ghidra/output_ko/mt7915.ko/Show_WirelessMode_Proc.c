// module: mt7915.ko
// function: Show_WirelessMode_Proc @ 0xd578c
// size: 372 bytes
//

undefined4 Show_WirelessMode_Proc(int *param_1,char *param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = *param_1;
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(iVar1 + 0x3c),*(undefined4 *)(iVar1 + 0x38),iVar1,
                     param_4);
  if (iVar1 != 0) {
    switch(*(undefined2 *)(iVar1 + 0x18)) {
    case 1:
      snprintf(param_2,param_3 & 0xff,"\t11A");
      break;
    case 2:
      snprintf(param_2,param_3 & 0xff,"\t11B");
      break;
    default:
      snprintf(param_2,param_3 & 0xff,"\tUnknow Value(%d)");
      break;
    case 4:
      snprintf(param_2,param_3 & 0xff,"\t11G");
      break;
    case 6:
      snprintf(param_2,param_3 & 0xff,"\t11B/G");
      break;
    case 7:
      snprintf(param_2,param_3 & 0xff,"\t11A/B/G");
      break;
    case 8:
      snprintf(param_2,param_3 & 0xff,"\t11N only with 2.4G");
      break;
    case 0xc:
      snprintf(param_2,param_3 & 0xff,"\t11G/N");
      break;
    case 0xe:
      snprintf(param_2,param_3 & 0xff,"\t11B/G/N");
      break;
    case 0x10:
      snprintf(param_2,param_3 & 0xff,"\t11N only with 5G");
      break;
    case 0x11:
      snprintf(param_2,param_3 & 0xff,"\t11A/N");
      break;
    case 0x1d:
      snprintf(param_2,param_3 & 0xff,"\t11A/G/N");
      break;
    case 0x1f:
      snprintf(param_2,param_3 & 0xff,"\t11A/B/G/N");
    }
  }
  return 0;
}

