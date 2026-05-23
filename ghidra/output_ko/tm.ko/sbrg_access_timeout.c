// module: tm.ko
// function: sbrg_access_timeout @ 0x1c5f8
// size: 148 bytes
//

uint sbrg_access_timeout(undefined4 param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  int local_1c [2];
  
  uVar3 = 0;
  uVar2 = 0;
  local_1c[0] = 0;
  do {
    uVar2 = uVar2 + 1;
    uVar1 = tmOnuRegRead(0x14,local_1c,0,&sbragRegTable);
    uVar3 = uVar1 | uVar3;
    bVar4 = uVar2 == 9;
    if (uVar2 < 10) {
      bVar4 = local_1c[0] == 0;
    }
  } while (bVar4);
  if (9 < uVar2) {
    if (g_tm_debug_level == 0) {
      uVar3 = 0xffffffff;
    }
    else {
      printk("[TM][%s]indirect access time out\n",param_1);
      uVar3 = 0xffffffff;
    }
  }
  return uVar3;
}

