// compatible: zte,zx279128-smp
// function: FUN_c06379dc @ 0xc06379dc
// found via struct field ptr -> 0xc06379dc
// total struct-refs for compat: 2
//

void FUN_c06379dc(undefined4 param_1,uint *param_2,uint *param_3)

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
  FUN_c02bb8cc(param_1,s_arm_tag_latency_c0584288,&local_2c,1);
  if (local_2c == 0) {
    uVar2 = 0;
    uVar3 = 0;
  }
  else {
    uVar3 = 0x1c0;
    uVar2 = (local_2c + -1) * 0x40;
  }
  FUN_c02bb8cc(param_1,s_arm_data_latency_c0584298,&local_20,2);
  if ((local_20 != 0) && (local_1c != 0)) {
    uVar3 = uVar3 | 0x3f;
    uVar2 = uVar2 | local_20 - 1U | (local_1c + -1) * 8;
  }
  FUN_c02bb8cc(param_1,s_arm_dirty_latency_c05844b8,&local_28,1);
  if (local_28 != 0) {
    uVar3 = uVar3 | 0xe00;
    uVar2 = uVar2 | (local_28 + -1) * 0x200;
  }
  iVar1 = FUN_c06374d8(param_1,param_2,param_3,&local_24,0x40000);
  if (iVar1 == 0) {
    if (local_24 < 9) {
      uVar3 = uVar3 | 0x1e000;
      uVar2 = uVar2 | local_24 << 0xd;
    }
    else {
      FUN_c046918c(&DAT_c05844cc);
      FUN_c046918c(&DAT_c0584504,local_24);
    }
    *param_2 = *param_2 & ~uVar3 | uVar2;
    *param_3 = ~uVar3 & *param_3;
  }
  return;
}

