// compatible: rohm,dh2228fv
// function: FUN_c0251f30 @ 0xc0251f30
// found via struct field ptr -> 0xc0251f30
// total struct-refs for compat: 2
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_c0251f30(uint param_1)

{
  undefined4 *puVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  
  if ((((*(int *)(param_1 + 0x114) != 0) &&
       (iVar2 = FUN_c02bcbd8(&DAT_c04bf0a8,param_1), iVar2 == 0)) &&
      (FUN_c01e9794(param_1,s_buggy_DT__spidev_listed_directly_c05b4e94),
      *(int *)(param_1 + 0x114) != 0)) && (iVar2 = FUN_c02bcbd8(&DAT_c04bf0a8,param_1), iVar2 == 0))
  {
    FUN_c0019ef8(s_drivers_spi_spidev_c_c05b4edc,0x2db);
  }
  puVar3 = (uint *)FUN_c00a2ff0(_DAT_c06a713c,0x80d0);
  if (puVar3 == (uint *)0x0) {
    uVar5 = 0xfffffff4;
  }
  else {
    puVar3[1] = 0;
    puVar3[2] = param_1;
    puVar6 = puVar3 + 3;
    FUN_c0045eb0(puVar3 + 5,s__spidev_>buf_lock_c05b4ebc,&DAT_c06ad220);
    puVar3[3] = (uint)puVar6;
    puVar3[4] = (uint)puVar6;
    FUN_c046fc7c(&DAT_c068de50);
    uVar4 = FUN_c01805f4(0xc06ad21c,0x20);
    if (uVar4 < 0x20) {
      *puVar3 = uVar4 | 0x9900000;
      uVar5 = FUN_c01ea520(_DAT_c06ad218,param_1,uVar4 | 0x9900000,puVar3,s_spidev_d__d_c05b4ed0,
                           (int)*(short *)(*(int *)(param_1 + 0x158) + 0x160),
                           *(undefined1 *)(param_1 + 0x160));
      if ((uVar5 < 0xfffff001) || (uVar5 == 0)) {
        FUN_c01819b0(uVar4,DAT_c02520e8);
        uVar5 = (uint)DAT_c068de68;
        puVar1 = (undefined4 *)((int)DAT_c068de68 + 4);
        DAT_c068de68 = puVar6;
        *puVar1 = puVar6;
        puVar3[4] = (uint)&DAT_c068de68;
        puVar3[3] = uVar5;
        FUN_c046fac0(&DAT_c068de50);
        puVar3[0xe] = *(uint *)(param_1 + 0x15c);
        *(uint **)(param_1 + 0x58) = puVar3;
        return 0;
      }
    }
    else {
      uVar5 = 0xffffffed;
    }
    FUN_c046fac0(&DAT_c068de50);
    puVar3[0xe] = *(uint *)(param_1 + 0x15c);
    FUN_c00a35dc(puVar3);
  }
  return uVar5;
}

