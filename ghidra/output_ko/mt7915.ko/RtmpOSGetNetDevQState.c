// module: mt7915.ko
// function: RtmpOSGetNetDevQState @ 0x2440f8
// size: 24 bytes
//

undefined4 RtmpOSGetNetDevQState(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x240) + param_2 * 0xe0;
  if (iVar2 == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    uVar1 = *(undefined4 *)(iVar2 + 0x50);
  }
  return uVar1;
}

