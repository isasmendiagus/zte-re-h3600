// module: mt7915.ko
// function: AsicGetChBusyCnt @ 0x131cb4
// size: 264 bytes
//

int AsicGetChBusyCnt(undefined4 param_1,int param_2,uint *param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 local_88 [2];
  int local_80;
  undefined4 local_78;
  int local_70;
  undefined4 local_68;
  int local_60;
  undefined4 local_58;
  undefined4 local_48;
  undefined4 local_38;
  int local_30;
  
  local_88[0] = 0x56;
  local_78 = 0x51;
  local_68 = 0x52;
  local_58 = 0x57;
  local_48 = 0xe;
  local_38 = 0xb;
  MtCmdMultipleMibRegAccessRead(param_1,param_2,local_88,6);
  if (param_3 == (uint *)0x0 || param_4 == 0) {
    iVar3 = param_2 << 2;
  }
  else {
    iVar3 = param_2 * 4;
    uVar1 = __aeabi_uidiv(((((local_70 + local_80 + local_60) -
                            *(int *)((int)&g_ulPreOBSSAirtime + param_2 * 4)) -
                           *(int *)((int)&g_ulMyTxAirtime + iVar3)) -
                          *(int *)((int)&g_ulMyRxAirtime + iVar3)) * 100,param_4 * 1000);
    if (uVar1 < 100) {
      *param_3 = uVar1;
    }
    else {
      *param_3 = 0x5f;
    }
  }
  *(int *)((int)&g_ulPreOBSSAirtime + param_2 * 4) = local_80;
  iVar2 = *(int *)((int)&PreBusyTime + iVar3);
  *(int *)((int)&g_ulMyTxAirtime + iVar3) = local_70;
  *(int *)((int)&g_ulMyRxAirtime + iVar3) = local_60;
  *(int *)((int)&PreBusyTime + iVar3) = local_30;
  return local_30 - iVar2;
}

