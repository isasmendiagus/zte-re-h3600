// module: mt7915.ko
// function: MT_MPSSetParm @ 0x27ced0
// size: 936 bytes
//

int MT_MPSSetParm(undefined4 param_1,undefined4 param_2,int param_3,uint *param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  uint *puVar5;
  uint uVar6;
  uint *puVar7;
  uint uVar8;
  
  iVar2 = net_ad_wrap_service();
  uVar6 = (uint)*(byte *)(iVar2 + 0x4cc);
  iVar2 = net_ad_wrap_service(param_1);
  uVar8 = *(uint *)(iVar2 + uVar6 * 0xd18 + 0x4e0);
  if ((0x400 < param_3 || param_3 == 0) || ((uVar8 & 0x40) != 0)) {
LAB_0027cf28:
    if (-1 < DebugLevel) {
      printk("%s-fail, control_band_idx:%u, items:%d, Mode:%x\n","MT_MPSSetParm",uVar6,param_3,uVar8
            );
    }
    return 1;
  }
  iVar2 = net_ad_wrap_service(param_1);
  iVar2 = iVar2 + uVar6 * 0xd18 + 0x11b0;
  puVar7 = *(uint **)(iVar2 + 0x1c);
  if (puVar7 == (uint *)0x0) {
    if (*(int *)(iVar2 + 8) == 0) {
      *(int *)(iVar2 + 8) = param_3;
      *(uint *)(iVar2 + 0xc) = uVar6;
      iVar1 = (param_3 + 1) * 0x18;
      iVar3 = os_alloc_mem(param_1,iVar2 + 0x1c,iVar1);
      if (iVar3 == 1) goto LAB_0027cf28;
      puVar7 = *(uint **)(iVar2 + 0x1c);
      if (iVar1 != 0) {
        __memzero(puVar7,iVar1);
        puVar7 = *(uint **)(iVar2 + 0x1c);
      }
    }
    else {
      iVar3 = 0;
    }
  }
  else {
    iVar3 = 0;
  }
  if (DebugLevel < 3) {
    switch(param_2) {
    case 0:
switchD_0027cf90_caseD_0:
      *puVar7 = 1;
      if (0 < param_3) {
        puVar5 = param_4;
        do {
          puVar4 = puVar5 + 1;
          puVar7 = puVar7 + 6;
          *puVar7 = *puVar5;
          puVar5 = puVar4;
        } while (puVar4 != param_4 + param_3);
      }
      break;
    case 1:
switchD_0027cf90_caseD_1:
      *puVar7 = 1;
      if (0 < param_3) {
        puVar5 = param_4;
        do {
          uVar6 = puVar7[6];
          puVar7[6] = uVar6 & 0xf0ffffff;
          puVar4 = puVar5 + 1;
          puVar7 = puVar7 + 6;
          *puVar7 = (*puVar5 & 0xf) << 0x18 | uVar6 & 0xf0ffffff;
          puVar5 = puVar4;
        } while (puVar4 != param_4 + param_3);
      }
      break;
    case 2:
switchD_0027cf90_caseD_2:
      *puVar7 = 1;
      if (0 < param_3) {
        puVar5 = param_4;
        do {
          uVar6 = puVar7[6];
          puVar7[6] = uVar6 & 0xff0000ff;
          puVar4 = puVar5 + 1;
          puVar7 = puVar7 + 6;
          *puVar7 = (*puVar5 & 0xffff) << 8 | uVar6 & 0xff0000ff;
          puVar5 = puVar4;
        } while (puVar4 != param_4 + param_3);
        return iVar3;
      }
      return iVar3;
    case 3:
switchD_0027cf90_caseD_3:
      *puVar7 = 1;
      if (0 < param_3) {
        puVar5 = param_4;
        do {
          uVar6 = puVar7[6];
          puVar7[6] = uVar6 & 0xffffff00;
          puVar4 = puVar5 + 1;
          puVar7 = puVar7 + 6;
          *puVar7 = *puVar5 & 0xff | uVar6 & 0xffffff00;
          puVar5 = puVar4;
        } while (puVar4 != param_4 + param_3);
        return iVar3;
      }
      return iVar3;
    case 4:
switchD_0027cf90_caseD_4:
      puVar7[1] = 1;
      if (0 < param_3) {
        puVar5 = param_4;
        do {
          puVar4 = puVar5 + 1;
          uVar6 = *puVar5;
          if (uVar6 < 0x5d9) {
            if (uVar6 < 0x19) {
              *puVar5 = 0x19;
              uVar6 = 0x19;
            }
          }
          else {
            *puVar5 = 0x5d8;
            uVar6 = 0x5d8;
          }
          puVar7[7] = uVar6;
          puVar7 = puVar7 + 6;
          puVar5 = puVar4;
        } while (puVar4 != param_4 + param_3);
        return iVar3;
      }
      return iVar3;
    case 5:
switchD_0027cf90_caseD_5:
      puVar7[2] = 1;
      if (0 < param_3) {
        puVar5 = param_4;
        do {
          puVar4 = puVar5 + 1;
          puVar7[8] = *puVar5;
          puVar5 = puVar4;
          puVar7 = puVar7 + 6;
        } while (puVar4 != param_4 + param_3);
        return iVar3;
      }
      return iVar3;
    case 6:
switchD_0027cf90_caseD_6:
      puVar7[3] = 1;
      if (0 < param_3) {
        puVar5 = param_4;
        do {
          puVar4 = puVar5 + 1;
          puVar7[9] = *puVar5;
          puVar5 = puVar4;
          puVar7 = puVar7 + 6;
        } while (puVar4 != param_4 + param_3);
        return iVar3;
      }
      return iVar3;
    default:
      break;
    case 8:
switchD_0027cf90_caseD_8:
      puVar7[4] = 1;
      if (0 < param_3) {
        puVar5 = param_4;
        do {
          puVar4 = puVar5 + 1;
          puVar7[10] = *puVar5;
          puVar5 = puVar4;
          puVar7 = puVar7 + 6;
        } while (puVar4 != param_4 + param_3);
        return iVar3;
      }
      return iVar3;
    case 9:
switchD_0027cf90_caseD_9:
      puVar7[5] = 1;
      if (0 < param_3) {
        puVar5 = param_4;
        do {
          puVar4 = puVar5 + 1;
          puVar7[0xb] = *puVar5;
          puVar5 = puVar4;
          puVar7 = puVar7 + 6;
        } while (puVar4 != param_4 + param_3);
      }
    }
    return iVar3;
  }
  printk("%s: control_band_idx:%u, items:%d, Mode:%x, mps_cb:%p, mps_set:%p, mps_cnt:%d\n",
         "MT_MPSSetParm",uVar6,param_3,uVar8,iVar2 + 4,puVar7,*(undefined4 *)(iVar2 + 8));
  switch(param_2) {
  case 0:
    goto switchD_0027cf90_caseD_0;
  case 1:
    goto switchD_0027cf90_caseD_1;
  case 2:
    goto switchD_0027cf90_caseD_2;
  case 3:
    goto switchD_0027cf90_caseD_3;
  case 4:
    goto switchD_0027cf90_caseD_4;
  case 5:
    goto switchD_0027cf90_caseD_5;
  case 6:
    goto switchD_0027cf90_caseD_6;
  default:
    if (2 < DebugLevel) {
      printk("%s: unknown setting type\n","MT_MPSSetParm");
      return iVar3;
    }
    return iVar3;
  case 8:
    goto switchD_0027cf90_caseD_8;
  case 9:
    goto switchD_0027cf90_caseD_9;
  }
}

