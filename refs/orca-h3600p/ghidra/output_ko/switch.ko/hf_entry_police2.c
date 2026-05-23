// module: switch.ko
// function: hf_entry_police2 @ 0x11c10
// size: 168 bytes
//

undefined4 hf_entry_police2(int param_1)

{
  undefined4 uVar1;
  uint *puVar2;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  if (param_1 == 0) {
    uVar1 = 0;
    if (g_switch_debug_level != 0) {
      printk("[%s] input ERROR: ptSession=NULL\n","hf_entry_police2");
      uVar1 = 0;
    }
  }
  else {
    zte_api_sw_fast_entry_policy(&local_10,&local_c,&local_18,&local_14);
    if (*(char *)(param_1 + 4) == '\0') {
      puVar2 = &DN_MAX_FAST_ENTRY;
    }
    else {
      puVar2 = &UP_MAX_FAST_ENTRY;
      local_14 = local_18;
      local_c = local_10;
    }
    if ((uint)(local_14 + local_c) < *puVar2) {
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}

