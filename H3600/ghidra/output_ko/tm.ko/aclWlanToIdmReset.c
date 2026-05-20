// module: tm.ko
// function: aclWlanToIdmReset @ 0x558e4
// size: 52 bytes
//

void aclWlanToIdmReset(void)

{
  undefined *puVar1;
  undefined *puVar2;
  
  puVar1 = &DAT_000c1176;
  do {
    puVar1[-2] = 0;
    puVar1[-1] = 0;
    puVar2 = puVar1 + 0x12;
    __memzero(puVar1,0x10);
    puVar1 = puVar2;
  } while (puVar2 != (undefined *)0xc1296);
  return;
}

