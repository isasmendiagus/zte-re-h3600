// module: tm.ko
// function: sadm_access_timeout @ 0x259a0
// size: 148 bytes
//

uint sadm_access_timeout(undefined4 param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  int local_1c [2];
  
  uVar4 = 0;
  uVar3 = 0;
  local_1c[0] = 0;
  do {
    uVar3 = uVar3 + 1;
    uVar1 = sadm_get_indacs_done(local_1c);
    uVar4 = uVar4 | uVar1;
    bVar5 = uVar3 == 0x13;
    if (uVar3 < 0x14) {
      bVar5 = local_1c[0] == 0;
    }
  } while (bVar5);
  if (0x13 < uVar3) {
    if ((g_tm_debug_level != 0) &&
       (iVar2 = ___ratelimit(_rs_14589,"sadm_access_timeout"), iVar2 != 0)) {
      printk("[TM][%s]indirect access time out\n",param_1);
    }
    uVar4 = 0xffffffff;
  }
  return uVar4;
}

