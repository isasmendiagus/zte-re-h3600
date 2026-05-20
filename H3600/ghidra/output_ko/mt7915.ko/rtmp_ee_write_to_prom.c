// module: mt7915.ko
// function: rtmp_ee_write_to_prom @ 0x1d1d4c
// size: 96 bytes
//

undefined4 rtmp_ee_write_to_prom(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined2 uVar1;
  int iVar2;
  int extraout_r1;
  int iVar3;
  code *pcVar4;
  int iVar5;
  
  iVar5 = 0;
  do {
    iVar3 = iVar5 * 2;
    iVar5 = iVar5 + 1;
    uVar1 = *(undefined2 *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + iVar3);
    iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0),param_2);
    pcVar4 = *(code **)(iVar2 + 0xc);
    if (pcVar4 != (code *)0x0) {
      (*pcVar4)(param_1,iVar3,uVar1,pcVar4,param_4);
      iVar3 = extraout_r1;
    }
    param_2 = iVar3;
  } while (iVar5 != 0x200);
  return 1;
}

