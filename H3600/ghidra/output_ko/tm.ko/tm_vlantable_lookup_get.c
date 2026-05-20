// module: tm.ko
// function: tm_vlantable_lookup_get @ 0x4b6a4
// size: 484 bytes
//

undefined4 tm_vlantable_lookup_get(int *param_1)

{
  int iVar1;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  undefined1 local_c;
  
  if (param_1 == (int *)0x0) {
    printk("ERROR:(%s:%d)","tm_api.c",0x4000);
    printk("param pp_entry is NULL\n");
    return 0xffffffff;
  }
  iVar1 = sbrg_lookup_vltbl(&local_2c);
  if (iVar1 != 0) {
    printk("ERROR:(%s:%d)","tm_api.c",0x4007);
    printk("tm_vlantable_lookup_get fail\n");
    return 0xffffffff;
  }
  *(undefined1 *)(param_1 + 10) = local_c;
  if (local_2c == 1) {
LAB_0004b6e8:
    *param_1 = local_2c;
  }
  else {
    if (local_2c != 0) {
      if (local_2c != 2) {
        local_2c = 3;
      }
      goto LAB_0004b6e8;
    }
    *param_1 = 0;
  }
  if (local_28 == 1) {
LAB_0004b704:
    param_1[1] = local_28;
  }
  else {
    if (local_28 != 0) {
      if (local_28 != 2) {
        local_28 = 3;
      }
      goto LAB_0004b704;
    }
    param_1[1] = 0;
  }
  if (local_24 == 1) {
LAB_0004b720:
    param_1[2] = local_24;
  }
  else {
    if (local_24 != 0) {
      if (local_24 != 2) {
        local_24 = 3;
      }
      goto LAB_0004b720;
    }
    param_1[2] = 0;
  }
  if (local_20 == 1) {
LAB_0004b73c:
    param_1[3] = local_20;
  }
  else {
    if (local_20 != 0) {
      if (local_20 != 2) {
        local_20 = 3;
      }
      goto LAB_0004b73c;
    }
    param_1[3] = 0;
  }
  if (local_1c == 1) {
LAB_0004b758:
    param_1[4] = local_1c;
  }
  else {
    if (local_1c != 0) {
      if (local_1c != 2) {
        local_1c = 3;
      }
      goto LAB_0004b758;
    }
    param_1[4] = 0;
  }
  if (local_18 == 1) {
LAB_0004b774:
    param_1[5] = local_18;
  }
  else {
    if (local_18 != 0) {
      if (local_18 != 2) {
        local_18 = 3;
      }
      goto LAB_0004b774;
    }
    param_1[5] = 0;
  }
  if (local_14 != 1) {
    if (local_14 == 0) {
      param_1[6] = 0;
      goto joined_r0x0004b79c;
    }
    if (local_14 != 2) {
      local_14 = 3;
    }
  }
  param_1[6] = local_14;
joined_r0x0004b79c:
  if (local_10 != 1) {
    if (local_10 == 0) {
      param_1[7] = 0;
      return 0;
    }
    if (local_10 != 2) {
      param_1[7] = 3;
      return 0;
    }
  }
  param_1[7] = local_10;
  return 0;
}

