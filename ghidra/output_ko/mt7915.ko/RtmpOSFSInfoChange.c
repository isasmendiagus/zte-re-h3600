// module: mt7915.ko
// function: RtmpOSFSInfoChange @ 0x245298
// size: 64 bytes
//

void RtmpOSFSInfoChange(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    *(undefined4 *)(((uint)&stack0x00000000 & 0xffffe03f) + 8) = *(undefined4 *)(param_1 + 8);
    return;
  }
  uVar1 = *(undefined4 *)(((uint)&stack0x00000000 & 0xffffe03f) + 8);
  *(undefined4 *)(((uint)&stack0x00000000 & 0xffffe03f) + 8) = 0;
  *(undefined4 *)(param_1 + 8) = uVar1;
  return;
}

