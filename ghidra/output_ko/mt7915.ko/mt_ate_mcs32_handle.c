// module: mt7915.ko
// function: mt_ate_mcs32_handle @ 0x286e0c
// size: 164 bytes
//

undefined4 mt_ate_mcs32_handle(int param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  
  uVar1 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  if (uVar1 == 0x7915 ||
      (uVar1 == 0x6867 ||
      (uVar1 == 0x7663 ||
      (uVar1 == 0x6632 ||
      (uVar1 == 0x7615 || (*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xfffb) == 0x7622))
      ))) {
    WtblDwSet(param_1,param_2,1,5,0xffffcfff,(param_3 & 3) << 0xc);
  }
  return 0;
}

