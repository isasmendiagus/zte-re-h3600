// module: mt7915.ko
// function: RtmpOSNetDevProtect @ 0x2442d8
// size: 16 bytes
//

void RtmpOSNetDevProtect(int param_1)

{
  if (param_1 == 0) {
    rtnl_unlock();
    return;
  }
  rtnl_lock();
  return;
}

