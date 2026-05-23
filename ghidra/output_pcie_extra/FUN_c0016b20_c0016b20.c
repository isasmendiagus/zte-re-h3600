// FUN_c0016b20 @ c0016b20

byte FUN_c0016b20(void)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  
  FUN_c01b1498(5);
  FUN_c01b1498(0xf);
  FUN_c01b1498(0x2f);
  bVar1 = FUN_c01b13a0(5);
  cVar2 = FUN_c01b13a0(0xf);
  cVar3 = FUN_c01b13a0(0x2f);
  return cVar3 << 5 | cVar2 << 1 | bVar1;
}

