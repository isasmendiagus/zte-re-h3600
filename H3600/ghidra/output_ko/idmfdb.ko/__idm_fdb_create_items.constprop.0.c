// module: idmfdb.ko
// function: __idm_fdb_create_items.constprop.0 @ 0x10e88
// size: 172 bytes
//

void __idm_fdb_create_items_constprop_0(int param_1,int param_2,int param_3,int *param_4)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  char *pcVar4;
  int iVar5;
  
  if (0 < param_2) {
    iVar2 = *param_4;
    if (iVar2 < 1) {
      iVar1 = 0;
    }
    else {
      puVar3 = (undefined4 *)(param_1 + -4);
      iVar1 = 0;
      iVar5 = 0;
      do {
        puVar3 = puVar3 + 1;
        pcVar4 = (char *)*puVar3;
        iVar5 = iVar5 + 1;
        if (((pcVar4 != (char *)0x0) && (*pcVar4 != '\0')) &&
           ((*(uint *)(*(int *)(pcVar4 + 0x14) + 0x30) & 1) != 0)) {
          *(undefined4 *)(param_3 + 0xc) = 0;
          *(char **)(param_3 + 8) = pcVar4;
          iVar1 = iVar1 + 1;
          iVar2 = *param_4;
          param_3 = param_3 + 0x18;
        }
      } while ((iVar5 != param_2) && (iVar1 < iVar2));
    }
    *param_4 = iVar2 - iVar1;
    return;
  }
  *param_4 = *param_4;
  return;
}

