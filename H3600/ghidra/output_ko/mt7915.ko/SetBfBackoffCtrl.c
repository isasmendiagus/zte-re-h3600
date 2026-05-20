// module: mt7915.ko
// function: SetBfBackoffCtrl @ 0xbf9bc
// size: 128 bytes
//

undefined4 SetBfBackoffCtrl(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  uint uVar2;
  
  if (*(char *)((int)param_1 + 0x286285) == '\x01') {
    uVar2 = *(uint *)(*param_1 + 0x3c) & 0xff;
    if (*(byte *)((int)param_1 + 0x2b7242) <= uVar2) {
      return 0;
    }
    uVar1 = HcGetBandByWdev(param_1 + uVar2 * 0x160d + 0xadc92,param_2,0x5834,
                            param_1 + uVar2 * 0x160d,param_4);
  }
  else {
    uVar1 = 0;
  }
  _SetBfBackoffCtrl(param_1,uVar1,param_2);
  return 1;
}

