// module: rtkatm.ko
// function: atm_carrier_write @ 0x107ac
// size: 368 bytes
//

uint atm_carrier_write(undefined4 param_1,uint param_2,uint param_3)

{
  size_t sVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined4 local_28;
  int local_24;
  char *local_20;
  char cStack_19;
  undefined4 local_18;
  undefined4 local_14;
  
  uVar7 = param_3;
  if (7 < param_3) {
    uVar7 = 8;
  }
  local_18 = 0;
  local_14 = 0;
  if (param_2 != 0) {
    uVar6 = *(uint *)(((uint)&local_28 & 0xffffe000) + 8);
    uVar4 = param_2 + uVar7;
    uVar5 = uVar4;
    if (!CARRY4(param_2,uVar7)) {
      uVar5 = uVar4 - (uVar6 + 1);
    }
    if (!CARRY4(param_2,uVar7) && uVar4 <= uVar6) {
      uVar6 = 0;
    }
    if (uVar6 == 0) {
      iVar2 = __copy_from_user(&local_18,param_2,uVar7);
      if (iVar2 == 0) {
LAB_00010808:
        sVar1 = strlen((char *)&local_18);
        (&cStack_19)[sVar1] = '\0';
        iVar2 = dev_get_by_name(&init_net,&_LC18);
        if (iVar2 == 0) {
          local_20 = "ERROR: Cannot find the net device\n";
          local_28 = 4;
          local_24 = iVar2;
          ProcKernLog("/home/ws/zx279128s/chip_zx279128s/kmodule/rtk_atm/rtk_atm.c",0x263,
                      "atm_carrier_write",0);
          param_3 = 0xffffffed;
        }
        else {
          iVar3 = strcmp((char *)&local_18,"up");
          if (iVar3 == 0) {
            isAdslup = 1;
            netif_carrier_on(iVar2);
          }
          else {
            iVar3 = strcmp((char *)&local_18,"down");
            if (iVar3 == 0) {
              isAdslup = 0;
              netif_carrier_off(iVar2);
            }
          }
        }
        return param_3;
      }
    }
    else {
      if (uVar7 == 0) goto LAB_00010808;
      __memzero(&local_18,uVar7,uVar5);
    }
  }
  return 0xfffffff2;
}

