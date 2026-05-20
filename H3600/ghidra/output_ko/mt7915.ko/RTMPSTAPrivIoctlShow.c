// module: mt7915.ko
// function: RTMPSTAPrivIoctlShow @ 0x59d7c
// size: 224 bytes
//

undefined4 RTMPSTAPrivIoctlShow(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  DAT_005f349c = &DAT_0032e7b8;
  iVar1 = DAT_0032e7b8;
  do {
    if (iVar1 == 0) {
LAB_00059e24:
      if (DebugLevel < 3) {
        return 0xffffffea;
      }
      printk("===>rt_ioctl_setparam:: (iwpriv) Not Support Show Command [%s=%s]\n",param_2,param_3);
      return 0xffffffea;
    }
    iVar1 = rtstrcasecmp(param_2,iVar1);
    if (iVar1 == 1) {
      iVar1 = (*(code *)DAT_005f349c[1])(param_1,param_3);
      if (iVar1 == 0) {
        return 1;
      }
      if (*DAT_005f349c != 0) {
        return 0;
      }
      goto LAB_00059e24;
    }
    iVar1 = DAT_005f349c[2];
    DAT_005f349c = DAT_005f349c + 2;
  } while( true );
}

