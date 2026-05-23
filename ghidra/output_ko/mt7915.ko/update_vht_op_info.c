// module: mt7915.ko
// function: update_vht_op_info @ 0x203628
// size: 224 bytes
//

void update_vht_op_info(uint param_1,byte *param_2,byte *param_3)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  code *UNRECOVERED_JUMPTABLE;
  
  bVar1 = param_2[1];
  bVar2 = param_2[2];
  if (param_3 == (byte *)0x0) {
    return;
  }
  bVar3 = *param_2;
  if (param_1 <= *param_2) {
    bVar3 = (byte)param_1;
  }
  *param_3 = bVar3;
  switch(*param_2) {
  case 0:
    goto switchD_00203654_caseD_0;
  case 1:
    if (param_1 != 1) {
      if (param_1 < 2) goto switchD_00203654_caseD_0;
      if (bVar2 != 0) {
        if (bVar1 < bVar2) {
          bVar3 = bVar2 - bVar1;
        }
        else {
          bVar3 = bVar1 - bVar2;
        }
        if (bVar3 == 8) {
          param_3[1] = bVar2;
          *param_3 = 2;
        }
        else if (0x10 < bVar3) {
          param_3[1] = bVar1;
          *param_3 = 3;
        }
        goto switchD_00203654_caseD_0;
      }
    }
    break;
  case 2:
  case 3:
    if (param_1 == 1) {
      *param_3 = 1;
    }
    break;
  default:
    param_3[1] = bVar1;
    *param_3 = 1;
    goto switchD_00203654_caseD_0;
  }
  param_3[1] = bVar1;
switchD_00203654_caseD_0:
                    /* WARNING: Could not recover jumptable at 0x002036b8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  if (0 < DebugLevel) {
    printk("%s, bw=%u, cent_ch=%u\n","update_vht_op_info",*param_3,param_3[1]);
    return;
  }
  (*UNRECOVERED_JUMPTABLE)();
  return;
}

