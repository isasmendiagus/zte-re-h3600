// module: mt7915.ko
// function: AsicRaParamStaRecUpdate @ 0x134c4c
// size: 356 bytes
//

undefined4 AsicRaParamStaRecUpdate(int param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  int *piVar5;
  undefined1 auStack_1c0 [204];
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 uStack_ec;
  undefined4 local_e8 [36];
  int *local_58;
  undefined4 local_54;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(int *)(iVar1 + 0x34) == 0) {
    AsicNotSupportFunc(param_1,"AsicRaParamStaRecUpdate");
    return 0;
  }
  os_zero_mem(&local_f4,0xd4);
  uVar2 = HcGetMaxStaNum(param_1);
  if (param_2 < uVar2) {
    piVar5 = (int *)(param_2 * 0x14c0 + param_1 + 0xa1d20);
    if (3 < DebugLevel) goto LAB_00134d94;
LAB_00134d28:
    if (piVar5 == (int *)0x0) goto LAB_00134cb8;
    if (*piVar5 != 0) {
      iVar4 = piVar5[2];
      if (iVar4 == 0) {
        printk(&_LC33,0x893);
        dump_stack();
        return 0xffffffff;
      }
      local_f0 = (uint)CONCAT21(local_f0._2_2_,*(undefined1 *)(iVar4 + 0x29)) << 8;
      local_f4 = CONCAT31(local_f4._1_3_,*(undefined1 *)(iVar4 + 0x999));
      goto LAB_00134cc4;
    }
  }
  else {
    if (3 < DebugLevel) {
      piVar5 = (int *)0x0;
LAB_00134d94:
      printk("%s::Wcid(%d), u4EnableFeature(%d)\n","AsicRaParamStaRecUpdate",param_2,param_4);
      goto LAB_00134d28;
    }
LAB_00134cb8:
    piVar5 = (int *)0x0;
  }
  local_f0 = CONCAT22(local_f0._2_2_,0xe00);
LAB_00134cc4:
  local_f0 = CONCAT31(local_f0._1_3_,1);
  local_f4 = CONCAT22((short)param_2,(undefined2)local_f4);
  local_e8[0] = param_4;
  local_58 = piVar5;
  local_54 = param_3;
  memcpy(auStack_1c0,local_e8,200);
  uVar3 = (**(code **)(iVar1 + 0x34))(param_1,local_f4,local_f0,uStack_ec);
  return uVar3;
}

