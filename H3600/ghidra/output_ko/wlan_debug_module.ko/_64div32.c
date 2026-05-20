// module: wlan_debug_module.ko
// function: _64div32 @ 0x11404
// size: 276 bytes
//

ulonglong _64div32(uint param_1,uint param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint extraout_r1;
  uint uVar4;
  uint extraout_r1_00;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  bool bVar11;
  bool bVar12;
  
  if (param_3 == 0) {
    uVar2 = 0;
    iVar8 = 0;
  }
  else {
    if (param_2 == 0) {
      uVar2 = __aeabi_uidiv(param_1,param_3);
      return (ulonglong)uVar2;
    }
    iVar8 = 0;
    __aeabi_uidivmod(param_2,param_3);
    uVar7 = 0x1f;
    uVar2 = __aeabi_uidiv(param_2,param_3);
    uVar9 = extraout_r1;
    do {
      uVar10 = uVar7 - 0x20;
      uVar6 = uVar7 & 0xff;
      uVar5 = 0x20 - uVar7;
      uVar4 = param_2 & (1 << (uVar10 & 0xff) | 1U >> (uVar5 & 0xff));
      uVar1 = uVar7 & 0xff;
      uVar7 = uVar7 - 1;
      uVar6 = ((param_1 & 1 << uVar6) >> uVar1 | uVar4 << (uVar5 & 0xff) | uVar4 >> (uVar10 & 0xff))
              + uVar9 * 2;
      bVar11 = uVar6 < uVar9;
      if (bVar11) {
        uVar6 = uVar6 - param_3;
      }
      __aeabi_uidivmod(uVar6,param_3);
      iVar3 = __aeabi_uidiv(uVar6,param_3);
      bVar12 = CARRY4(uVar2,uVar2);
      uVar9 = uVar2 * 2;
      uVar6 = (uint)bVar11 + iVar3;
      uVar2 = uVar9 + uVar6;
      iVar8 = iVar8 * 2 + (uint)bVar12 + (uint)CARRY4(uVar9,uVar6);
      uVar9 = extraout_r1_00;
    } while (uVar7 != 0xffffffff);
  }
  return CONCAT44(iVar8,uVar2);
}

