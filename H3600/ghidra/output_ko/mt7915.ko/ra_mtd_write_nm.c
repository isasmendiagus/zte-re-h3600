// module: mt7915.ko
// function: ra_mtd_write_nm @ 0x156904
// size: 156 bytes
//

undefined4
ra_mtd_write_nm(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5)

{
  uint uVar1;
  undefined1 auStack_24 [16];
  
  uVar1 = RtmpOSFileOpen("/wlan/caldata",0x41,0);
  if ((uVar1 != 0) && (uVar1 < 0xfffff001)) {
    RtmpOSFSInfoChange(auStack_24,1);
    RtmpOSFileSeek(uVar1,param_3);
    RtmpOSFileWrite(uVar1,param_1,param_5);
    vfs_fsync(uVar1,0);
    RtmpOSFileClose(uVar1);
    RtmpOSFSInfoChange(auStack_24,0);
    return param_5;
  }
  return 0xffffffff;
}

