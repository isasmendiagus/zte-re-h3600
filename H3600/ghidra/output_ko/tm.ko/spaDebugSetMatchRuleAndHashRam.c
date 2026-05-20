// module: tm.ko
// function: spaDebugSetMatchRuleAndHashRam @ 0x6f66c
// size: 832 bytes
//

undefined4 spaDebugSetMatchRuleAndHashRam(void)

{
  uint local_38;
  ushort local_34;
  undefined1 local_32;
  undefined1 local_31;
  undefined1 local_30;
  undefined1 local_2f;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined2 local_2c;
  undefined2 local_2a;
  
  __memzero(&local_32,10);
  local_2c = 0xff;
  local_2a = 0x11;
  local_32 = 0;
  local_2d = 0;
  local_31 = 1;
  local_30 = 1;
  local_2f = 2;
  local_2e = 4;
  spa_set_matchram(&local_32);
  local_32 = 1;
  local_2a = 6;
  spa_set_matchram(&local_32);
  local_32 = 2;
  local_31 = 1;
  local_30 = 1;
  local_2f = 2;
  local_2d = 0;
  local_2e = 0xb;
  local_2c = 0xffff;
  local_2a = 0x208;
  spa_set_matchram(&local_32);
  local_31 = 1;
  local_30 = 1;
  local_2f = 2;
  local_2e = 0xb;
  local_2d = 0;
  local_2c = 0xffff;
  local_32 = 3;
  local_2a = 0x13f;
  spa_set_matchram(&local_32);
  local_32 = 4;
  local_2a = 0x140;
  spa_set_matchram(&local_32);
  local_32 = 5;
  local_2a = 0x76c;
  spa_set_matchram(&local_32);
  local_32 = 6;
  local_2a = 0xb3;
  spa_set_matchram(&local_32);
  local_2e = 10;
  local_2d = 1;
  local_32 = 7;
  local_2a = 0x42;
  spa_set_matchram(&local_32);
  local_2d = 2;
  local_2a = 0x45;
  local_32 = 8;
  spa_set_matchram(&local_32);
  local_2e = 0xb;
  local_2d = 1;
  local_2a = 0x42;
  local_32 = 9;
  spa_set_matchram(&local_32);
  local_32 = 10;
  local_2e = 0xb;
  local_2d = 2;
  local_2a = 0x45;
  spa_set_matchram(&local_32);
  __memzero(&local_38,6);
  local_34 = local_34 & 0xfe00 | 0x200;
  local_38 = 0xaa9;
  spa_set_hashram(0,&local_38);
  local_38 = (uint)((ushort)local_38 & 0xfe03 | 0x8c);
  local_34 = local_34 & 0xfe00;
  local_38 = local_38 & 0x1ff | 0x1200;
  spa_set_hashram(1,&local_38);
  local_38 = (uint)((ushort)local_38 & 0xfe03 | 0x8c);
  local_34 = local_34 & 0xfe00;
  local_38 = local_38 & 0x1ff | 0x2200;
  spa_set_hashram(2,&local_38);
  local_38 = (uint)((ushort)local_38 & 0xfe03 | 0xa4);
  local_34 = local_34 & 0xfe00;
  local_38 = local_38 & 0x1ff | 0x4200;
  spa_set_hashram(2,&local_38);
  local_38 = (uint)((ushort)local_38 & 0xfe03 | 0xa0);
  local_34 = local_34 & 0xfe00;
  local_38 = local_38 & 0x1ff | 0x8200;
  spa_set_hashram(3,&local_38);
  local_38 = (uint)((ushort)local_38 & 0xfe03 | 0xa0);
  local_34 = local_34 & 0xfe00;
  local_38 = local_38 & 0x1ff | 0x18400;
  spa_set_hashram(4,&local_38);
  local_38 = (uint)((ushort)local_38 & 0xfe03 | 0x74);
  local_34 = local_34 & 0xfe00;
  local_38 = local_38 & 0x1ff | 0xf0200;
  spa_set_hashram(5,&local_38);
  return 0;
}

