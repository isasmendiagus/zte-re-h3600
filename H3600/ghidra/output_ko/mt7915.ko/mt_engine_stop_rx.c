// module: mt7915.ko
// function: mt_engine_stop_rx @ 0x256f34
// size: 212 bytes
//

int mt_engine_stop_rx(undefined4 param_1,uint *param_2,undefined4 *param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = *param_2;
  iVar1 = (*(code *)*param_3)(param_1,1,0);
  if ((iVar1 == 0) && (iVar1 = (*(code *)*param_3)(param_1,6,0,param_4), iVar1 == 0)) {
    *param_2 = uVar2 & 0xfffffffb;
    if (*(char *)((int)param_2 + 0xc55) == '\n') {
      (*(code *)param_3[0x52])
                (param_1,param_4,3,0,*(undefined1 *)((int)param_2 + 0xc57),(char)param_2[0x317],
                 *(undefined1 *)((int)param_2 + 0xc5a),(char)param_2[0x2ff],param_2 + 0x14f);
    }
    else if (*(char *)((int)param_2 + 0xc55) == '\v') {
      (*(code *)param_3[0x53])(param_1,param_4,0xf800);
    }
  }
  return iVar1;
}

