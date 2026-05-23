// module: plat-zxylzb_9128S.ko
// function: myfile_read @ 0x11818
// size: 88 bytes
//

undefined4 myfile_read(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 uStack_10;
  
  if (param_2 != 0 && param_1 != 0) {
    uVar3 = (uint)&uStack_10 & 0xffffe000;
    uVar2 = *(undefined4 *)(uVar3 + 8);
    *(undefined4 *)(uVar3 + 8) = 0;
    uStack_10 = param_4;
    uVar1 = (**(code **)(*(int *)(param_1 + 0x14) + 8))();
    *(undefined4 *)(((uint)&uStack_10 & 0xffffe000) + 8) = uVar2;
    return uVar1;
  }
  return 0xffffffff;
}

