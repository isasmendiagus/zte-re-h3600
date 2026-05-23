// module: mt7915.ko
// function: create_sae_instance @ 0x208f0c
// size: 704 bytes
//

int create_sae_instance(undefined4 param_1,int param_2,int param_3,int param_4,int param_5,
                       int param_6,int *param_7,char param_8)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar2 = hc_get_chip_wtbl_max_num(*(undefined4 *)(*(int *)(param_2 + 0x1b924) + 0xa797a0));
  if (2 < DebugLevel) {
    printk("==> %s()\n","create_sae_instance");
  }
  if (((param_3 == 0 || param_2 == 0) || (param_5 == 0 || param_4 == 0)) ||
     (param_8 == '\0' && param_6 == 0)) {
    if (-1 < DebugLevel) {
      printk("%s():input should not be null\n","create_sae_instance");
    }
  }
  else if ((param_8 == '\0') || ((param_7 != (int *)0x0 && (param_7 != (int *)*param_7)))) {
    if (*(int *)(param_2 + 0x1b908) != iVar2) {
LAB_00208fcc:
      _raw_spin_lock_bh(param_2 + 0x1b928);
      if (iVar2 == 0) {
        iVar2 = 0;
      }
      else {
        if (*(char *)(param_2 + 0x128) == '\0') {
          iVar3 = 0;
        }
        else {
          iVar3 = 0;
          iVar4 = param_2;
          do {
            iVar3 = iVar3 + 1;
            if (iVar2 == iVar3) {
              iVar2 = 0;
              goto LAB_00209028;
            }
            pcVar1 = (char *)(iVar4 + 0x2b0);
            iVar4 = iVar4 + 0x188;
          } while (*pcVar1 != '\0');
        }
        iVar2 = param_2 + iVar3 * 0x188;
        sae_ins_init(param_1,param_2,iVar2,param_3,param_4,param_5,param_6,param_7,param_8);
        *(undefined1 *)(iVar2 + 0x128) = 1;
        *(int *)(param_2 + 0x1b908) = *(int *)(param_2 + 0x1b908) + 1;
      }
LAB_00209028:
      _raw_spin_unlock_bh(param_2 + 0x1b928);
      return iVar2;
    }
    iVar3 = hc_get_chip_wtbl_max_num(*(undefined4 *)(*(int *)(param_2 + 0x1b924) + 0xa797a0));
    if (iVar3 != 0) {
      iVar6 = 0;
      iVar5 = 0;
      iVar4 = param_2;
      do {
        iVar5 = iVar5 + 1;
        if (*(char *)(iVar4 + 0x128) != '\0') {
          if (*(int *)(iVar4 + 0x17c) != 0) {
            if (*(char *)(*(int *)(iVar4 + 0x17c) + 0x128) == '\x01') {
              iVar6 = iVar6 + 1;
              delete_sae_instance();
            }
            *(undefined4 *)(iVar4 + 0x17c) = 0;
          }
          if (*(char *)(iVar4 + 0x129) == '\x01') {
            iVar6 = iVar6 + 1;
            delete_sae_instance(iVar4);
          }
        }
        iVar4 = iVar4 + 0x188;
      } while (iVar5 != iVar3);
      if (iVar6 != 0) goto LAB_00208fcc;
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s():pwd id is null or empty\n","create_sae_instance");
  }
  return 0;
}

