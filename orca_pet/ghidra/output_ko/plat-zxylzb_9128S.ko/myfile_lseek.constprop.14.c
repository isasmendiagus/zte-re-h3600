// module: plat-zxylzb_9128S.ko
// function: myfile_lseek.constprop.14 @ 0x11940
// size: 96 bytes
//

undefined4 myfile_lseek_constprop_14(int param_1,int param_2)

{
  undefined4 uVar1;
  code *pcVar2;
  undefined4 uVar3;
  undefined4 local_18 [2];
  
  if (param_1 != 0) {
    uVar3 = *(undefined4 *)(((uint)local_18 & 0xffffe000) + 8);
    *(undefined4 *)(((uint)local_18 & 0xffffe000) + 8) = 0;
    local_18[0] = 0;
    pcVar2 = *(code **)(*(int *)(param_1 + 0x14) + 4);
    uVar1 = (*pcVar2)(param_1,pcVar2,param_2,param_2 >> 0x1f);
    *(undefined4 *)(((uint)local_18 & 0xffffe000) + 8) = uVar3;
    return uVar1;
  }
  return 0xffffffff;
}

