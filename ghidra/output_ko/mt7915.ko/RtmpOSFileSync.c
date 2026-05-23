// module: mt7915.ko
// function: RtmpOSFileSync @ 0x1568fc
// size: 8 bytes
//

void RtmpOSFileSync(undefined4 param_1)

{
  vfs_fsync(param_1,0);
  return;
}

