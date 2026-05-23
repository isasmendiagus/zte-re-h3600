// module: mt7915.ko
// function: build_extended_cap_ie @ 0x1473e0
// size: 76 bytes
//

void build_extended_cap_ie(undefined4 param_1,undefined4 *param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_2[4];
  iVar2 = *(int *)(iVar1 + 0x14);
  if (((iVar2 != 4) && (iVar2 != 0x10)) && (iVar2 != 2)) {
    build_ap_extended_cap_ie(param_1,iVar1,*param_2);
    return;
  }
  build_sta_extended_cap_ie(param_1,iVar1,*param_2,param_3);
  return;
}

