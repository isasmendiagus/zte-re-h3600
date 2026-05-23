// module: mt7915.ko
// function: set_vow_watf_sta_dwrr @ 0x48948
// size: 500 bytes
//

void set_vow_watf_sta_dwrr(int param_1,undefined1 *param_2,int param_3)

{
  byte bVar1;
  undefined1 uVar2;
  bool bVar3;
  int iVar4;
  void *pvVar5;
  uint uVar6;
  uint uVar7;
  void *__s1;
  void *pvVar8;
  int local_38;
  
  if (*(char *)(param_1 + 0xa7a32c) == '\0') {
    return;
  }
  uVar6 = 0;
  pvVar5 = (void *)(param_1 + 0xa7a332);
  uVar7 = 0;
  local_38 = DebugLevel;
  bVar3 = false;
  do {
    bVar1 = *(byte *)((int)pvVar5 + -1);
    if (bVar1 != 0) {
      __s1 = pvVar5;
      do {
        pvVar8 = (void *)((int)__s1 + 6);
        iVar4 = memcmp(__s1,param_2,6);
        if (iVar4 == 0) {
          uVar7 = uVar6 & 0xff;
          if (local_38 < 0) {
            bVar3 = true;
          }
          else {
            bVar3 = true;
            printk("This MAC Address %02x:%02x:%02x:%02x:%02x:%02x is found in list.\n",*param_2,
                   param_2[1],param_2[2],param_2[3],param_2[4],param_2[5]);
            local_38 = DebugLevel;
          }
          break;
        }
        __s1 = pvVar8;
      } while (pvVar8 != (void *)((int)pvVar5 + (short)(bVar1 - 1 & 0xff) * 6 + 6));
    }
    uVar6 = uVar6 + 1;
    pvVar5 = (void *)((int)pvVar5 + 0x6c1);
  } while (uVar6 != 4);
  uVar2 = (undefined1)uVar7;
  if (bVar3) {
    iVar4 = param_1 + param_3 * 8;
    *(undefined1 *)(param_1 + (param_3 + 0x14f33d) * 8) = uVar2;
    *(undefined1 *)(iVar4 + 0xa799e9) = uVar2;
    *(undefined1 *)(iVar4 + 0xa799ea) = uVar2;
    *(undefined1 *)(iVar4 + 0xa799eb) = uVar2;
    if (-1 < local_38) {
      uVar6 = 0x7f44;
      goto LAB_00048ae8;
    }
  }
  else {
    iVar4 = param_1 + param_3 * 8;
    *(undefined1 *)(param_1 + (param_3 + 0x14f33d) * 8) = uVar2;
    *(undefined1 *)(iVar4 + 0xa799e9) = uVar2;
    *(undefined1 *)(iVar4 + 0xa799ea) = uVar2;
    *(undefined1 *)(iVar4 + 0xa799eb) = uVar2;
    if (-1 < local_38) {
      uVar6 = 0x7f6c;
LAB_00048ae8:
      printk(uVar6 | 0x2b0000,param_3,uVar7);
      return;
    }
  }
  return;
}

