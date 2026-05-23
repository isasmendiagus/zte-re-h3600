// compatible: zte,zx279127-i2c
// function: FUN_c02aabe4 @ 0xc02aabe4
// found via struct field ptr -> 0xc02aabe4
// total struct-refs for compat: 2
//

int FUN_c02aabe4(int param_1,undefined4 *param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  int local_1c;
  
  iVar2 = (int)(param_2 + 0xfe580f4) >> 4;
  if (iVar2 == 0x3a) {
    local_1c = *(int *)(**(int **)(param_1 + 0x58) + 4);
    iVar2 = FUN_c018bafc(param_3,&DAT_c05d6350,(&PTR_s_Unknown_c04c9dcc)[local_1c]);
    return iVar2;
  }
  iVar1 = FUN_c02aa1ac(*(int **)(param_1 + 0x58),iVar2,&local_1c);
  if (iVar1 < 0) {
    if ((iVar1 != -0x3d) && (iVar1 != -0x13)) {
      FUN_c01e7918(param_1,s_driver_failed_to_report___s__pro_c05be888,*param_2,iVar1);
    }
  }
  else {
    if (iVar2 == 0) {
      iVar2 = FUN_c018bafc(param_3,&DAT_c05d6350,(&PTR_s_Unknown_c04c9dec)[local_1c]);
      return iVar2;
    }
    if (iVar2 == 1) {
      iVar1 = FUN_c018bafc(param_3,&DAT_c05d6350,(&PTR_s_Unknown_c04c9e00)[local_1c]);
    }
    else if (iVar2 == 2) {
      iVar1 = FUN_c018bafc(param_3,&DAT_c05d6350,(&PTR_s_Unknown_c04c9e10)[local_1c]);
    }
    else if (iVar2 == 6) {
      iVar1 = FUN_c018bafc(param_3,&DAT_c05d6350,(&PTR_s_Unknown_c04c9e34)[local_1c]);
    }
    else if (iVar2 == 0x2d) {
      iVar1 = FUN_c018bafc(param_3,&DAT_c05d6350,(&PTR_s_Unknown_c04c9e50)[local_1c]);
    }
    else if (iVar2 == 0x3b) {
      iVar1 = FUN_c018bafc(param_3,&DAT_c05d6350,*(undefined4 *)(&DAT_c04c9e68 + local_1c * 4));
    }
    else {
      if (iVar2 < 0x3e) {
        puVar3 = &DAT_c05d4680;
      }
      else {
        puVar3 = &DAT_c05d6350;
      }
      iVar1 = FUN_c018bafc(param_3,puVar3,local_1c);
    }
  }
  return iVar1;
}

