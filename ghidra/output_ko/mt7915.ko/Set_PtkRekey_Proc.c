// module: mt7915.ko
// function: Set_PtkRekey_Proc @ 0x17e4c
// size: 332 bytes
//

undefined4 Set_PtkRekey_Proc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  
  cVar1 = os_str_tol(param_2,0,10,param_4,param_4);
  uVar2 = HcGetMaxStaNum(param_1);
  uVar5 = (int)cVar1 & 0xffff;
  if ((uVar2 <= uVar5) || (iVar4 = param_1 + uVar5 * 0x14c0, *(int *)(iVar4 + 0xa1d20) != 0x20001))
  {
    return 0;
  }
  uVar2 = *(uint *)(iVar4 + 0xa1e9c);
  iVar6 = iVar4 + 0xa1e9c;
  if ((uVar2 & 0x2090) == 0) {
    if ((uVar2 & 0x40) != 0) {
      iVar3 = is_pmkid_cache_in_sec_config(iVar6);
      if (iVar3 != 0) goto LAB_00017ed8;
      uVar2 = *(uint *)(iVar4 + 0xa1e9c);
    }
    if ((uVar2 & 0x10000) == 0) {
      return 1;
    }
    iVar4 = is_pmkid_cache_in_sec_config(iVar6);
    if (iVar4 == 0) {
      return 1;
    }
  }
LAB_00017ed8:
  iVar4 = param_1 + uVar5 * 0x14c0;
  *(undefined1 *)(iVar4 + 0xa2234) = 8;
  *(undefined1 *)(iVar4 + 0xa2274) = 0;
  *(undefined4 *)(iVar4 + 0xa27fc) = 1;
  WPABuildPairMsg1(param_1,iVar6,param_1 + uVar5 * 0x14c0 + 0xa1d20);
  if (DebugLevel < 1) {
    return 1;
  }
  printk("%s::(WCID=%d)\n","Set_PtkRekey_Proc",uVar5);
  return 1;
}

