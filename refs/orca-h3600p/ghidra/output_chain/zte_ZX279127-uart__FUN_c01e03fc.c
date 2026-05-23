// compatible: zte,ZX279127-uart
// function: FUN_c01e03fc @ 0xc01e03fc
// found via struct field ptr -> 0xc01e03fc
// total struct-refs for compat: 2
//

uint FUN_c01e03fc(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  int iVar7;
  uint uVar8;
  undefined4 uVar9;
  int iVar10;
  
  iVar10 = param_1 + 0x10;
  uVar9 = *(undefined4 *)(param_1 + 0x124);
  iVar4 = FUN_c01ed3bc(iVar10,0x178,0x80d0);
  if (iVar4 == 0) {
    return 0xfffffff4;
  }
  uVar5 = FUN_c02bb9c0(uVar9,s_usb_serial_c05bd72c + 4);
  if (-1 < (int)uVar5) {
    puVar6 = (undefined4 *)FUN_c01eb908(param_1,0x200,0);
    if (puVar6 == (undefined4 *)0x0) {
      uVar8 = 0xffffffed;
    }
    else {
      iVar7 = FUN_c01979a4(iVar10,puVar6);
      if (iVar7 == 0) {
        return 0xfffffff4;
      }
      uVar8 = FUN_c02c1c34(iVar10,0);
      *(uint *)(iVar4 + 0xf8) = uVar8;
      if (uVar8 < 0xfffff001) {
        *(int *)(iVar4 + 0xc0) = iVar10;
        uVar1 = DAT_c0696a3c;
        uVar9 = DAT_c0696a38;
        *(undefined4 *)(iVar4 + 0x100) = DAT_c0696a50;
        uVar2 = DAT_c0696a44;
        *(undefined4 *)(iVar4 + 0x114) = uVar9;
        *(undefined4 *)(iVar4 + 0x118) = uVar1;
        uVar3 = DAT_c0696a4c;
        uVar9 = DAT_c0696a40;
        *(undefined4 *)(iVar4 + 0x120) = uVar2;
        uVar1 = DAT_c0696a48;
        *(undefined4 *)(iVar4 + 0x11c) = uVar9;
        *(undefined4 *)(iVar4 + 0x128) = uVar3;
        *(undefined4 *)(iVar4 + 0x124) = uVar1;
        *(undefined **)(iVar4 + 0xfc) = &DAT_c0696a34;
        *(undefined4 *)(iVar4 + 300) = 0;
        *(undefined4 *)(iVar4 + 0x110) = 0x10;
        uVar9 = *puVar6;
        *(int *)(iVar4 + 8) = iVar7;
        *(undefined1 *)(iVar4 + 0x4e) = 2;
        *(undefined4 *)(iVar4 + 0xb8) = uVar9;
        uVar9 = FUN_c01ec070(param_1,0);
        *(undefined4 *)(iVar4 + 0x130) = 0xffffffe0;
        *(code **)(iVar4 + 0x13c) = FUN_c01e0a1c;
        *(undefined4 *)(iVar4 + 0x48) = *(undefined4 *)(iVar4 + 0x110);
        *(uint *)(iVar4 + 0xb0) = uVar5;
        *(undefined4 *)(iVar4 + 0x90) = 0x10000000;
        *(int *)(iVar4 + 0x134) = iVar4 + 0x134;
        *(int *)(iVar4 + 0x138) = iVar4 + 0x134;
        *(undefined4 *)(iVar4 + 0x3c) = uVar9;
        *(undefined ***)(iVar4 + 0xa8) = &PTR_FUN_c0696a5c;
        FUN_c0057694(iVar4 + 0x140,2,0,0);
        *(undefined1 **)(iVar4 + 0x150) = &LAB_c002a488;
        *(int *)(iVar4 + 0x154) = iVar4 + 0x130;
        FUN_c01dfd4c(iVar4,0,0xe);
        FUN_c01dfd4c(iVar4,0xffff,0x11);
        *(int *)(param_1 + 0x68) = iVar4;
        *(int *)(&DAT_c06bbf74 + uVar5 * 4) = iVar4;
        if ((uVar5 == 0) && (uVar8 = FUN_c01de08c(&DAT_c0696a08), (int)uVar8 < 0)) {
          FUN_c01e7918(iVar10,s_Failed_to_register_AMBA_PL011_dr_c05a6a00);
        }
        else {
          uVar8 = FUN_c01de568(DAT_c01e062c,iVar4);
          if (uVar8 != 0) {
            *(undefined4 *)(&DAT_c06bbf74 + uVar5 * 4) = 0;
          }
        }
      }
    }
    return uVar8;
  }
  FUN_c01e7918(iVar10,s_failed_to_get_alias_id___d_c05a69e4,uVar5);
  return uVar5;
}

