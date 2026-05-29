/* ===== FUN FUN_40e50998 @ 40e50998 =====
 * callers: 40e21050:FUN_40e21050
 * callees: 40e2a184:FUN_40e2a184, 40e2a6ec:FUN_40e2a6ec, 40e2a914:FUN_40e2a914, 40e455b8:FUN_40e455b8, 40e45800:FUN_40e45800, 40e45880:FUN_40e45880, 40e46930:FUN_40e46930, 40e4b7d4:FUN_40e4b7d4, 40e4b888:FUN_40e4b888
 */


void FUN_40e50998(void)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar3 = FUN_40e2a914(0x40);
  if (iVar3 == 0) {
    FUN_40e2a6ec();
    return;
  }
  FUN_40e45800(iVar3,0,0x40);
  uVar2 = DAT_40e50a30/*=0x47f3ed60*/;
  *(undefined4 *)(iVar3 + 0x20) = DAT_40e50a2c/*=0x47f2fc40*/;
  *(undefined4 *)(iVar3 + 0x2c) = DAT_40e50a34/*=0x47f2fc70*/;
  *(undefined4 *)(iVar3 + 0x24) = DAT_40e50a38/*=0x47f30054*/;
  *(undefined4 *)(iVar3 + 0x28) = DAT_40e50a3c/*=0x47f2fd10*/;
  FUN_40e46930(iVar3,uVar2);
  iVar4 = FUN_40e4b888(DAT_40e50a40/*=0x47f35f60*/,iVar3 + 0x10);
  if (iVar4 == 0) {
    FUN_40e2a184(DAT_40e50a44/*=0x47f3ed65*/);
  }
  else {
    FUN_40e45880(DAT_40e50a48/*=0x47f4af88*/,iVar3 + 0x10,6);
  }
  FUN_40e455b8();
  piVar1 = DAT_40e4bc88/*=0x47f574dc*/;
  iVar5 = DAT_40e4bc88/*=0x47f574dc*/[1];
  iVar4 = iVar5;
  if (iVar5 == 0) {
    DAT_40e4bc88/*=0x47f574dc*/[1] = iVar3;
    *piVar1 = iVar3;
    FUN_40e4b7d4();
  }
  else {
    do {
      iVar6 = iVar4;
      iVar4 = *(int *)(iVar6 + 0x34);
    } while (iVar4 != iVar5);
    *(int *)(iVar6 + 0x34) = iVar3;
  }
  iVar4 = piVar1[1];
  *(undefined4 *)(iVar3 + 0x1c) = 0;
  *(int *)(iVar3 + 0x34) = iVar4;
  iVar4 = piVar1[2];
  piVar1[2] = iVar4 + 1;
  *(int *)(iVar3 + 0x38) = iVar4;
  return;
}
