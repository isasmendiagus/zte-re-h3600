// module: mt7915.ko
// function: AsicSetSlotTime @ 0x133368
// size: 428 bytes
//

void AsicSetSlotTime(int param_1,int param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 uVar5;
  bool bVar6;
  
  iVar1 = GetStaCfgByWdev(param_1,param_4);
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    uVar4 = *(uint *)(param_1 + 0x795124);
    if (param_2 == 0) {
      if ((uVar4 & 8) == 0) {
        return;
      }
      uVar5 = 0x14;
      *(uint *)(param_1 + 0x795124) = uVar4 & 0xfffffff7;
    }
    else {
      if ((uVar4 & 8) != 0) {
        return;
      }
      uVar5 = 9;
      *(uint *)(param_1 + 0x795124) = uVar4 | 8;
    }
    goto LAB_00133414;
  }
  if (*(char *)(param_1 + 0x286285) != '\0') {
    uVar5 = 0;
    goto LAB_00133414;
  }
  bVar6 = param_3 == 0xe;
  if (param_3 < 0xf) {
    bVar6 = param_2 == 0;
  }
  uVar4 = *(uint *)(iVar1 + 0x212464);
  if (bVar6) {
    if ((uVar4 & 8) == 0) {
      return;
    }
    uVar5 = 0x14;
    *(uint *)(iVar1 + 0x212464) = uVar4 & 0xfffffff7;
  }
  else {
    if ((uVar4 & 8) != 0) {
      return;
    }
    uVar5 = 9;
    *(uint *)(iVar1 + 0x212464) = uVar4 | 8;
  }
  iVar2 = wlan_config_get_ba_enable(param_4);
  if (*(char *)(iVar1 + 0x40e0) == '\0') {
    if ((*(uint *)(param_1 + 0x795124) & 0x100) == 0) goto LAB_001334b0;
  }
  else if (iVar2 != 0 || *(char *)(iVar1 + 0x40e0) != '\x01') {
LAB_001334b0:
    if (*(char *)(param_1 + 0x795071) != '\0') {
      uVar5 = 9;
      *(uint *)(iVar1 + 0x212464) = *(uint *)(iVar1 + 0x212464) | 8;
    }
  }
  if (*(char *)(iVar1 + 0x4060) == '\0') {
    uVar5 = 0x14;
    *(uint *)(iVar1 + 0x212464) = *(uint *)(iVar1 + 0x212464) & 0xfffffff7;
  }
LAB_00133414:
  uVar3 = HcGetBandByChannel(param_1,param_3);
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0xa8) == (code *)0x0) {
    AsicNotSupportFunc(param_1,"AsicSetSlotTime");
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00133454. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0xa8))(param_1,uVar5,10,uVar3);
  return;
}

