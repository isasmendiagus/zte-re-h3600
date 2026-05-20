// module: plat-zxylzb_9128S.ko
// function: netdebug_dev_ioctl @ 0x1ae78
// size: 664 bytes
//

undefined4 netdebug_dev_ioctl(undefined4 param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  undefined1 auStack_20 [4];
  undefined4 local_1c;
  uint local_18;
  uint local_14;
  
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  switch(param_2) {
  case 0x100:
    uVar3 = *(uint *)(((uint)auStack_20 & 0xffffe000) + 8);
    uVar1 = param_3 + 0xc;
    uVar2 = uVar1;
    if (param_3 < 0xfffffff4) {
      uVar2 = uVar1 - (uVar3 + 1);
    }
    if (param_3 < 0xfffffff4 && uVar1 <= uVar3) {
      uVar3 = 0;
    }
    if (uVar3 == 0) {
      __copy_from_user(&local_1c,param_3,0xc);
    }
    else {
      __memzero(&local_1c,0xc,uVar2);
    }
    uVar2 = *(uint *)(((uint)auStack_20 & 0xffffe000) + 8);
    if (param_3 < 0xfffffff4 && param_3 + 0xc <= uVar2) {
      uVar2 = 0;
    }
    local_14 = (*(uint *)(&g_netdebug_mod_tabel + (local_18 >> 5) * 4) & 1 << (local_18 & 0x1f)) >>
               (local_18 & 0x1f);
    if (uVar2 != 0) {
      return 0;
    }
    __copy_to_user(param_3,&local_1c,0xc);
    return 0;
  case 0x101:
    uVar3 = *(uint *)(((uint)auStack_20 & 0xffffe000) + 8);
    uVar1 = param_3 + 0xc;
    uVar2 = uVar1;
    if (param_3 < 0xfffffff4) {
      uVar2 = uVar1 - (uVar3 + 1);
    }
    if (param_3 < 0xfffffff4 && uVar1 <= uVar3) {
      uVar3 = 0;
    }
    if (uVar3 == 0) {
      __copy_from_user(&local_1c,param_3,0xc);
    }
    else {
      __memzero(&local_1c,0xc,uVar2);
    }
    uVar2 = local_18 >> 5;
    if (local_14 == 0) {
      *(undefined4 *)(&g_netdebug_mod_tabel + uVar2 * 4) = 0;
    }
    else {
      *(uint *)(&g_netdebug_mod_tabel + uVar2 * 4) =
           *(uint *)(&g_netdebug_mod_tabel + uVar2 * 4) | 1 << (local_18 & 0x1f);
    }
    return 0;
  case 0x102:
    local_18 = g_netdebug_outuni;
    break;
  case 0x103:
    uVar3 = *(uint *)(((uint)auStack_20 & 0xffffe000) + 8);
    uVar1 = param_3 + 0xc;
    uVar2 = uVar1;
    if (param_3 < 0xfffffff4) {
      uVar2 = uVar1 - (uVar3 + 1);
    }
    if (param_3 < 0xfffffff4 && uVar1 <= uVar3) {
      uVar3 = 0;
    }
    if (uVar3 == 0) {
      __copy_from_user(&local_1c,param_3,0xc);
    }
    else {
      __memzero(&local_1c,0xc,uVar2);
    }
    g_netdebug_outuni = local_18;
    return 0;
  case 0x104:
    local_18 = g_netdebug_print;
    break;
  case 0x105:
    uVar3 = *(uint *)(((uint)auStack_20 & 0xffffe000) + 8);
    uVar1 = param_3 + 0xc;
    uVar2 = uVar1;
    if (param_3 < 0xfffffff4) {
      uVar2 = uVar1 - (uVar3 + 1);
    }
    if (param_3 < 0xfffffff4 && uVar1 <= uVar3) {
      uVar3 = 0;
    }
    if (uVar3 == 0) {
      __copy_from_user(&local_1c,param_3,0xc);
    }
    else {
      __memzero(&local_1c,0xc,uVar2);
    }
    g_netdebug_print = local_18;
    return 0;
  default:
    printk("module-netdebug: invalid cmdid\n");
    return 0;
  }
  uVar2 = *(uint *)(((uint)auStack_20 & 0xffffe000) + 8);
  if (param_3 < 0xfffffff4 && param_3 + 0xc <= uVar2) {
    uVar2 = 0;
  }
  if (uVar2 == 0) {
    __copy_to_user(param_3,&local_1c,0xc);
  }
  return 0;
}

