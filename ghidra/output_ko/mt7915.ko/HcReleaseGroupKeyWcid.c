// module: mt7915.ko
// function: HcReleaseGroupKeyWcid @ 0xa9f48
// size: 36 bytes
//

void HcReleaseGroupKeyWcid(int param_1,int param_2)

{
  undefined2 uVar1;
  
  uVar1 = WtcReleaseGroupKeyWcid
                    (*(undefined4 *)(param_1 + 0xa797a0),*(undefined4 *)(param_2 + 0xabc));
  *(undefined2 *)(param_2 + 0x10) = uVar1;
  return;
}

