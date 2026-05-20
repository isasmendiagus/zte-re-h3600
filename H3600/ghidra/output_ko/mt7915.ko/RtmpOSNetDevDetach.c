// module: mt7915.ko
// function: RtmpOSNetDevDetach @ 0x2442bc
// size: 28 bytes
//

void RtmpOSNetDevDetach(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)(param_1 + 300);
  unregister_netdevice_queue(param_1,0);
  vfree(uVar1);
  return;
}

