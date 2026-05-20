// compatible: zte,zx279127-i2c
// function: FUN_c02a9f58 @ 0xc02a9f58
// found via struct field ptr -> 0xc02a9f58
// total struct-refs for compat: 2
//

int FUN_c02a9f58(int param_1,undefined4 *param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  int local_1c;
  
  iVar2 = (int)(param_2 + 0xfe5c177) >> 4;
  if (iVar2 == 0x3a) {
    local_1c = *(int *)(**(int **)(param_1 + 0x58) + 4);
    iVar2 = FUN_c018b83c(param_3,&DAT_c05d7d7c,(&PTR_s_Unknown_c04ca4f0)[local_1c]);
    return iVar2;
  }
  iVar1 = FUN_c02a9520(*(int **)(param_1 + 0x58),iVar2,&local_1c);
  if (iVar1 < 0) {
    if ((iVar1 != -0x3d) && (iVar1 != -0x13)) {
      FUN_c01e9794(param_1,s_driver_failed_to_report___s__pro_c05bfbb4,*param_2,iVar1);
    }
  }
  else {
    if (iVar2 == 0) {
      iVar2 = FUN_c018b83c(param_3,&DAT_c05d7d7c,(&PTR_s_Unknown_c04ca510)[local_1c]);
      return iVar2;
    }
    if (iVar2 == 1) {
      iVar1 = FUN_c018b83c(param_3,&DAT_c05d7d7c,(&PTR_s_Unknown_c04ca524)[local_1c]);
    }
    else if (iVar2 == 2) {
      iVar1 = FUN_c018b83c(param_3,&DAT_c05d7d7c,(&PTR_s_Unknown_c04ca534)[local_1c]);
    }
    else if (iVar2 == 6) {
      iVar1 = FUN_c018b83c(param_3,&DAT_c05d7d7c,(&PTR_s_Unknown_c04ca558)[local_1c]);
    }
    else if (iVar2 == 0x2d) {
      iVar1 = FUN_c018b83c(param_3,&DAT_c05d7d7c,(&PTR_s_Unknown_c04ca574)[local_1c]);
    }
    else if (iVar2 == 0x3b) {
      iVar1 = FUN_c018b83c(param_3,&DAT_c05d7d7c,*(undefined4 *)(&DAT_c04ca58c + local_1c * 4));
    }
    else {
      if (iVar2 < 0x3e) {
        puVar3 = &DAT_c05d6074;
      }
      else {
        puVar3 = &DAT_c05d7d7c;
      }
      iVar1 = FUN_c018b83c(param_3,puVar3,local_1c);
    }
  }
  return iVar1;
}

