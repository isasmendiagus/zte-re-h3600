// module: mt7915.ko
// function: os_file_close @ 0x1429c4
// size: 60 bytes
//

int os_file_close(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  uStack_c = param_2;
  uStack_8 = param_3;
  uStack_4 = param_4;
  iVar1 = RtmpOSFileClose(param_1);
  if (iVar1 == 0) {
    RtmpOSFSInfoChange(&uStack_c,0);
  }
  return iVar1;
}

