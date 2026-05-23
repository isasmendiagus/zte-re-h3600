// module: mt7915.ko
// function: RtmpNetEthConvertDevSearch @ 0x2461b8
// size: 100 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

code * RtmpNetEthConvertDevSearch(undefined4 param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  code *pcVar3;
  
  pcVar3 = _release_firmware + -0x34;
  if (_release_firmware != release_firmware) {
    do {
      if ((*(short *)(pcVar3 + 0x150) == 1) &&
         (iVar2 = os_equal_mem(*(undefined4 *)(pcVar3 + 0x1dc),param_2 + 6,pcVar3[0x179]),
         iVar2 != 0)) {
        return pcVar3;
      }
      pcVar1 = pcVar3 + 0x34;
      pcVar3 = *(code **)pcVar1 + -0x34;
    } while (*(code **)pcVar1 != release_firmware);
  }
  return pcVar3;
}

