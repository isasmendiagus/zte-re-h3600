// compatible: zte,zx279128-smp
// function: FUN_c06389dc @ 0xc06389dc
// found via struct field ptr -> 0xc06389dc
// total struct-refs for compat: 2
//

void FUN_c06389dc(undefined4 param_1,uint *param_2,uint *param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int local_2c;
  int local_28;
  uint local_24;
  int local_20;
  int local_1c;
  
  local_20 = 0;
  local_1c = 0;
  local_2c = 0;
  local_28 = 0;
  FUN_c02bac40(param_1,s_arm_tag_latency_c0585458,&local_2c,1);
  if (local_2c == 0) {
    uVar2 = 0;
    uVar3 = 0;
  }
  else {
    uVar3 = 0x1c0;
    uVar2 = (local_2c + -1) * 0x40;
  }
  FUN_c02bac40(param_1,s_arm_data_latency_c0585468,&local_20,2);
  if ((local_20 != 0) && (local_1c != 0)) {
    uVar3 = uVar3 | 0x3f;
    uVar2 = uVar2 | local_20 - 1U | (local_1c + -1) * 8;
  }
  FUN_c02bac40(param_1,s_arm_dirty_latency_c0585688,&local_28,1);
  if (local_28 != 0) {
    uVar3 = uVar3 | 0xe00;
    uVar2 = uVar2 | (local_28 + -1) * 0x200;
  }
  iVar1 = FUN_c06384d8(param_1,param_2,param_3,&local_24,0x40000);
  if (iVar1 == 0) {
    if (local_24 < 9) {
      uVar3 = uVar3 | 0x1e000;
      uVar2 = uVar2 | local_24 << 0xd;
    }
    else {
      FUN_c046ab98(&DAT_c058569c);
      FUN_c046ab98(&DAT_c05856d4,local_24);
    }
    *param_2 = *param_2 & ~uVar3 | uVar2;
    *param_3 = ~uVar3 & *param_3;
  }
  return;
}

