// compatible: zte,zx279127-i2c
// function: FUN_c02a9158 @ 0xc02a9158
// found via struct field ptr -> 0xc02a9158
// total struct-refs for compat: 2
//

uint FUN_c02a9158(int param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  
  uVar8 = *(undefined4 *)(param_1 + 0x124);
  FUN_c046ab98(s_I2C_probe_start__c05bfa20);
  puVar1 = (undefined4 *)FUN_c01ed784(param_1,0x200,0);
  if (puVar1 == (undefined4 *)0x0) {
    uVar2 = 0xffffffed;
  }
  else {
    iVar3 = FUN_c01edeec(param_1,0);
    iVar7 = param_1 + 0x10;
    piVar4 = (int *)FUN_c01ef238(iVar7,0x230,0x80d0);
    if (piVar4 == (int *)0x0) {
      uVar2 = 0xfffffff4;
    }
    else {
      uVar2 = FUN_c02c0fa8(iVar7,0);
      piVar4[0x89] = uVar2;
      if (uVar2 < 0xfffff001) {
        uVar9 = *(undefined4 *)(param_1 + 4);
        if (uVar2 == 0) {
          uVar5 = 0;
        }
        else {
          uVar5 = FUN_c02c2a84();
        }
        FUN_c046ab98(&DAT_c05bfa34,uVar9,uVar9,uVar2,uVar5);
        FUN_c0044b0c(piVar4 + 2,s__i2c_>wait_c05bfa6c,&DAT_c06ad878);
        iVar6 = FUN_c01973f0(iVar7,puVar1);
        *piVar4 = iVar6;
        if (iVar6 == 0) {
          uVar2 = 0xfffffff4;
          FUN_c046ab98(s_get_i2c_reg_base_addr_failed_c05bfa78);
        }
        else {
          piVar4[1] = iVar3;
          iVar6 = FUN_c02bad34(uVar8,&DAT_c05bf45c);
          piVar4[6] = 0;
          piVar4[0x66] = iVar6;
          FUN_c018b7bc(piVar4 + 0x67,0x30,s_zx_i2c_at_0x_08x_c05bfa98,*puVar1);
          piVar4[0x83] = (int)FUN_c02a93c0;
          piVar4[0x87] = (int)FUN_c02a9434;
          piVar4[0x84] = (int)FUN_c02a8f3c;
          piVar4[0x85] = (int)FUN_c02a8e4c;
          piVar4[0x10] = iVar7;
          piVar4[9] = (int)(piVar4 + 0x82);
          piVar4[0x82] = (int)piVar4;
          iVar7 = FUN_c02c2a84(piVar4[0x89]);
          piVar4[0x86] = (int)&LAB_c02a8cdc;
          piVar4[0x88] = iVar7;
          iVar7 = FUN_c02a9138(piVar4 + 6);
          if (-1 < iVar7) {
            *(int **)(param_1 + 0x68) = piVar4;
            FUN_c046ab98(s_I2C_probe_successed__c05bfaac);
            return 0;
          }
          if (iVar3 != 0) {
            FUN_c004ccd4(iVar3,piVar4);
          }
          uVar2 = 0xffffffed;
        }
        FUN_c00a35dc(piVar4);
      }
    }
  }
  return uVar2;
}

