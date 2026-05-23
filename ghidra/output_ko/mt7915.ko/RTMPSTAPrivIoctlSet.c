// module: mt7915.ko
// function: RTMPSTAPrivIoctlSet @ 0x59ca0
// size: 220 bytes
//

undefined4 RTMPSTAPrivIoctlSet(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  _LANCHOR1 = &_LANCHOR2;
  iVar1 = _LANCHOR2;
  do {
    if (iVar1 == 0) {
LAB_00059d44:
      if (DebugLevel < 3) {
        return 0xffffffea;
      }
      printk("===>rt_ioctl_setparam:: (iwpriv) Not Support Set Command [%s=%s]\n",param_2,param_3);
      return 0xffffffea;
    }
    iVar1 = rtstrcasecmp(param_2,iVar1);
    if (iVar1 == 1) {
      iVar1 = (*(code *)_LANCHOR1[1])(param_1,param_3);
      if (iVar1 == 0) {
        return 1;
      }
      if (*_LANCHOR1 != 0) {
        return 0;
      }
      goto LAB_00059d44;
    }
    iVar1 = _LANCHOR1[2];
    _LANCHOR1 = _LANCHOR1 + 2;
  } while( true );
}

