// module: mt7915.ko
// function: HwEnterPsNull @ 0xaeee8
// size: 72 bytes
//

undefined4 HwEnterPsNull(int param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = GetAssociatedAPByWdev(param_1,**(undefined4 **)(param_2 + 8));
  RTMPSendNullFrame(param_1,uVar1,*(undefined1 *)(param_1 + 0x794cd0),1,1);
  return 0;
}

