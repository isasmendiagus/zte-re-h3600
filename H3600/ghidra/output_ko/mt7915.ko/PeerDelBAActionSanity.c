// module: mt7915.ko
// function: PeerDelBAActionSanity @ 0x110abc
// size: 44 bytes
//

bool PeerDelBAActionSanity(undefined4 param_1,uint param_2,undefined4 param_3,int param_4)

{
  uint uVar1;
  
  if (param_4 == 0x1e) {
    uVar1 = HcGetMaxStaNum();
    return param_2 < uVar1;
  }
  return false;
}

