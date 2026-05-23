// compatible: rohm,dh2228fv
// function: FUN_c0254198 @ 0xc0254198
// found via struct field ptr -> 0xc0254198
// total struct-refs for compat: 2
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_c0254198(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  short *psVar9;
  uint local_2c [2];
  
  iVar6 = *(int *)(param_1 + 0x124);
  iVar7 = *(int *)(param_1 + 100);
  FUN_c046918c(s_zx_spi_probe____c05b3c08);
  iVar2 = FUN_c01eb908(param_1,0x200,0);
  if (iVar2 != 0) {
    if (iVar7 == 0 && iVar6 == 0) {
      FUN_c046918c(s_can_t_get_the_platform_data_c05b3c18);
      return -0x16;
    }
    iVar2 = FUN_c02bb8cc(iVar6,s_spi_num_chipselects_c05b3c38,local_2c,1);
    if (iVar2 < 0) {
      if (iVar7 == 0) {
        return iVar2;
      }
      local_2c[0] = (uint)*(byte *)(iVar7 + 0xb);
    }
    iVar8 = param_1 + 0x10;
    iVar2 = FUN_c0250a40(iVar8,(local_2c[0] + 0x1c) * 4);
    if (iVar2 == 0) {
      return -0xc;
    }
    iVar3 = FUN_c00a3238(_DAT_c06b7058,0x80d0);
    if (iVar3 != 0) {
      *(int *)(param_1 + 0x68) = iVar2;
      if (iVar6 == 0) {
        sVar1 = *(short *)(param_1 + 4);
      }
      else {
        sVar1 = FUN_c02bb9c0(iVar6,&DAT_c05b3c4c);
      }
      psVar9 = (short *)(iVar2 + 0x160);
      *psVar9 = sVar1;
      FUN_c046918c(s_master_>bus_num__d_c05b3c50,(int)sVar1);
      iVar6 = *(int *)(iVar2 + 0x58);
      if (iVar7 == 0) {
        iVar7 = iVar3;
      }
      *(short *)(iVar2 + 0x162) = (short)local_2c[0];
      *(int *)(iVar6 + 0x28) = iVar7;
      iVar3 = FUN_c01e6e9c(iVar2);
      *(undefined1 **)(iVar6 + 0x10) = &LAB_c0253e88;
      *(code **)(iVar6 + 0xc) = FUN_c0254094;
      *(code **)(iVar6 + 0x14) = FUN_c0254494;
      iVar7 = iVar2;
      if (iVar3 == 0) {
        iVar7 = 0;
      }
      *(int *)(iVar6 + 8) = iVar7;
      *(code **)(iVar7 + 0x198) = FUN_c0253f38;
      *(undefined4 *)(*(int *)(iVar6 + 8) + 0x1a0) = 0;
      *(undefined4 *)(*(int *)(iVar6 + 8) + 0x19c) = 0;
      *(undefined2 *)(*(int *)(iVar6 + 8) + 0x166) = 7;
      uVar4 = FUN_c01eb908(param_1,0x200,0);
      uVar5 = FUN_c01979a4(iVar8,uVar4);
      if (uVar5 < 0xfffff001) {
        *(uint *)(*(int *)(iVar6 + 0x28) + 4) = uVar5;
        uVar5 = FUN_c02c1c34(iVar8,0);
        *(uint *)(iVar6 + 0x2c) = uVar5;
        if (uVar5 < 0xfffff001) {
          iVar7 = FUN_c02c3688();
          if ((iVar7 == 0) && (iVar7 = FUN_c02c3090(uVar5), iVar7 != 0)) {
            FUN_c02c3d34(uVar5);
          }
          *(undefined4 *)(iVar6 + 0x50) = 0;
          FUN_c0044d54(iVar6 + 0x54,s__x_>wait_c05853a0,&DAT_c06bd968);
          *(undefined4 *)(iVar6 + 0x60) = 0;
          FUN_c0044d54(iVar6 + 100,s__x_>wait_c05853a0,&DAT_c06bd968);
          FUN_c00460f8(iVar6 + 0x38,s__spi_>mutex_c05b3c84,&DAT_c06bd968);
          *(undefined4 *)(iVar2 + 0x114) = *(undefined4 *)(param_1 + 0x124);
          iVar7 = FUN_c0253d78(iVar6);
          if (iVar7 == 0) {
            FUN_c046918c(s_SPI_d_probed_c05b3cb8,(int)*psVar9);
            return 0;
          }
          FUN_c046918c(s_bitbang_start_failed_with__d_for_c05b3c90,iVar7,(int)*psVar9);
          FUN_c02c3d60(*(undefined4 *)(iVar6 + 0x2c));
          thunk_FUN_c02c54dc(*(undefined4 *)(iVar6 + 0x2c));
        }
        else {
          FUN_c046918c(s_unable_to_get_clock_for_SPI_d_c05b3c64,(int)*psVar9);
          iVar7 = *(int *)(iVar6 + 0x2c);
        }
      }
      else {
        iVar7 = *(int *)(*(int *)(iVar6 + 0x28) + 4);
      }
      FUN_c01e6ecc(iVar2);
      FUN_c00a3824(iVar2);
      *(undefined4 *)(param_1 + 0x68) = 0;
      return iVar7;
    }
  }
  return -0x13;
}

