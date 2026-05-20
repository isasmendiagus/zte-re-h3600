// module: tm.ko
// function: spa_print_match_ram @ 0x3bd64
// size: 48 bytes
//

undefined4 spa_print_match_ram(void)

{
  int iVar1;
  int iVar2;
  undefined1 auStack_12 [10];
  
  iVar1 = 0;
  do {
    iVar2 = iVar1 + 1;
    spa_get_matchram(iVar1,auStack_12);
    iVar1 = iVar2;
  } while (iVar2 != 8);
  return 0;
}

