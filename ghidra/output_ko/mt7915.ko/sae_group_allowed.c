// module: mt7915.ko
// function: sae_group_allowed @ 0x20af58
// size: 308 bytes
//

uint sae_group_allowed(int *param_1,byte *param_2,uint param_3)

{
  byte bVar1;
  uint uVar2;
  undefined1 *puVar3;
  
  if (4 < DebugLevel) {
    printk("==> %s():\n","sae_group_allowed");
  }
  if (param_2 == (byte *)0x0) {
LAB_0020afc8:
    if (param_1 == (int *)0x0) {
      return 0;
    }
    if (*(ushort *)(param_1 + 0xb) == param_3) {
      return 0;
    }
    if (*param_1 == 2) {
      return 0xffff;
    }
    sae_clear_data(param_1);
    switch(param_3) {
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
    case 0x1e:
      puVar3 = ecc_group_op;
      param_1[0x26] = (int)ecc_group_op;
      break;
    default:
      switch(param_3) {
      case 1:
      case 2:
      case 5:
      case 0xe:
      case 0xf:
      case 0x10:
      case 0x11:
      case 0x12:
      case 0x16:
      case 0x17:
      case 0x18:
        puVar3 = ffc_group_op;
        param_1[0x26] = (int)ffc_group_op;
        break;
      default:
        goto switchD_0020b07c_caseD_3;
      }
    }
    (**(code **)puVar3)(param_1,param_3);
    if (param_1[0x1b] == 0) {
      uVar2 = 1;
    }
    else {
      uVar2 = (uint)(param_1[0x26] == 0);
    }
  }
  else {
    bVar1 = *param_2;
    while (bVar1 != 0) {
      if (bVar1 == param_3) goto LAB_0020afc8;
      param_2 = param_2 + 1;
      bVar1 = *param_2;
    }
    if (param_3 == 0) goto LAB_0020afc8;
switchD_0020b07c_caseD_3:
    uVar2 = 0x4d;
  }
  return uVar2;
}

