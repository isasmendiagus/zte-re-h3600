// module: mt7915.ko
// function: AsicUpdateProtect @ 0x131efc
// size: 632 bytes
//

void AsicUpdateProtect(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int *piVar6;
  undefined1 uStack_3c;
  undefined1 local_3b;
  undefined1 local_3a;
  undefined1 local_39;
  undefined1 local_38;
  undefined1 local_37;
  undefined2 local_34;
  undefined1 local_32;
  undefined1 local_31;
  undefined1 local_30;
  undefined1 local_2f;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined2 local_2a;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  os_zero_mem(&uStack_3c,10);
  os_zero_mem(&local_32,10);
  if (*(code **)(iVar1 + 0x14) == (code *)0x0) {
    AsicNotSupportFunc(param_1,"AsicUpdateProtect");
  }
  else if (*(char *)(iVar2 + 0x15f) == '\x01') {
    (**(code **)(iVar1 + 0x14))(param_1,param_2);
  }
  else {
    iVar2 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
    piVar6 = (int *)(param_1 + 8);
    do {
      piVar6 = piVar6 + 1;
      iVar5 = *piVar6;
      if (iVar5 == 0) break;
      uVar4 = *(uint *)(iVar5 + 0x8dc);
      if ((*(char *)(param_1 + 0x79504d) == '\x01') && (iVar3 = HcGetBandByWdev(iVar5), iVar3 == 1))
      {
        if ((uVar4 & 0x20) != 0) {
          local_2a = 0x1f;
        }
        if ((uVar4 & 2) != 0) {
          local_30 = 1;
          local_2f = local_30;
          local_2d = local_30;
        }
        if ((uVar4 & 4) != 0) {
          local_2d = 1;
        }
        if ((uVar4 & 8) != 0) {
          local_2f = 1;
          local_30 = 1;
          local_2d = 1;
        }
        if ((uVar4 & 0x80) != 0) {
          local_2f = 1;
        }
        if ((*(uint *)(param_1 + 0xa39f84) & 0x100000) != 0) {
          local_31 = 1;
        }
        if ((uVar4 & 0x40) != 0) {
          local_31 = 1;
        }
        if ((uVar4 & 0x100) != 0) {
          local_31 = 1;
          local_2e = 1;
        }
        if ((uVar4 & 0x400) != 0) {
LAB_00132130:
          (**(code **)(iVar2 + 0x18))(param_1,iVar5,0,1);
          return;
        }
        local_32 = 1;
      }
      else {
        if ((uVar4 & 0x20) != 0) {
          local_34 = 0x1f;
        }
        if ((uVar4 & 2) != 0) {
          local_3a = 1;
          local_39 = local_3a;
          local_37 = local_3a;
        }
        if ((uVar4 & 4) != 0) {
          local_37 = 1;
        }
        if ((uVar4 & 8) != 0) {
          local_39 = 1;
          local_3a = 1;
          local_37 = 1;
        }
        if ((uVar4 & 0x80) != 0) {
          local_39 = 1;
        }
        if ((*(uint *)(param_1 + 0xa39f84) & 0x100000) != 0) {
          local_3b = 1;
        }
        if ((uVar4 & 0x40) != 0) {
          local_3b = 1;
        }
        if ((uVar4 & 0x100) != 0) {
          local_3b = 1;
          local_38 = 1;
        }
        if ((uVar4 & 0x400) != 0) goto LAB_00132130;
      }
      if (((uVar4 & 0x10) != 0) && (-1 < DebugLevel)) {
        printk("[ERROR] NOT Defined HT Protection!\n");
      }
    } while (piVar6 != (int *)(param_1 + 0x1a8));
    (**(code **)(iVar1 + 0x14))(param_1,&uStack_3c);
    if (*(char *)(param_1 + 0x79504d) == '\x01') {
      (**(code **)(iVar1 + 0x14))(param_1,&local_32);
    }
  }
  return;
}

