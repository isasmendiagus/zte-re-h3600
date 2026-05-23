// compatible: zte,zx279127-i2c
// function: FUN_c02a9de4 @ 0xc02a9de4
// found via struct field ptr -> 0xc02a9de4
// total struct-refs for compat: 2
//

uint FUN_c02a9de4(int param_1)

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
  FUN_c046918c(s_I2C_probe_start__c05be6f4);
  puVar1 = (undefined4 *)FUN_c01eb908(param_1,0x200,0);
  if (puVar1 == (undefined4 *)0x0) {
    uVar2 = 0xffffffed;
  }
  else {
    iVar3 = FUN_c01ec070(param_1,0);
    iVar7 = param_1 + 0x10;
    piVar4 = (int *)FUN_c01ed3bc(iVar7,0x230,0x80d0);
    if (piVar4 == (int *)0x0) {
      uVar2 = 0xfffffff4;
    }
    else {
      uVar2 = FUN_c02c1c34(iVar7,0);
      piVar4[0x89] = uVar2;
      if (uVar2 < 0xfffff001) {
        uVar9 = *(undefined4 *)(param_1 + 4);
        if (uVar2 == 0) {
          uVar5 = 0;
        }
        else {
          uVar5 = FUN_c02c3710();
        }
        FUN_c046918c(&DAT_c05be708,uVar9,uVar9,uVar2,uVar5);
        FUN_c0044d54(piVar4 + 2,s__i2c_>wait_c05be740,&DAT_c06bdfc0);
        iVar6 = FUN_c01979a4(iVar7,puVar1);
        *piVar4 = iVar6;
        if (iVar6 == 0) {
          uVar2 = 0xfffffff4;
          FUN_c046918c(s_get_i2c_reg_base_addr_failed_c05be74c);
        }
        else {
          piVar4[1] = iVar3;
          iVar6 = FUN_c02bb9c0(uVar8,&DAT_c05be130);
          piVar4[6] = 0;
          piVar4[0x66] = iVar6;
          FUN_c018ba7c(piVar4 + 0x67,0x30,s_zx_i2c_at_0x_08x_c05be76c,*puVar1);
          piVar4[0x83] = (int)FUN_c02aa04c;
          piVar4[0x87] = (int)FUN_c02aa0c0;
          piVar4[0x84] = (int)FUN_c02a9bbc;
          piVar4[0x85] = (int)FUN_c02a9acc;
          piVar4[0x10] = iVar7;
          piVar4[9] = (int)(piVar4 + 0x82);
          piVar4[0x82] = (int)piVar4;
          iVar7 = FUN_c02c3710(piVar4[0x89]);
          piVar4[0x86] = (int)&LAB_c02a995c;
          piVar4[0x88] = iVar7;
          iVar7 = FUN_c02a9dc4(piVar4 + 6);
          if (-1 < iVar7) {
            *(int **)(param_1 + 0x68) = piVar4;
            FUN_c046918c(s_I2C_probe_successed__c05be780);
            return 0;
          }
          if (iVar3 != 0) {
            FUN_c004cf1c(iVar3,piVar4);
          }
          uVar2 = 0xffffffed;
        }
        FUN_c00a3824(piVar4);
      }
    }
  }
  return uVar2;
}

