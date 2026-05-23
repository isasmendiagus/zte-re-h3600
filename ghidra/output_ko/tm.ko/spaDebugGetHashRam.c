// module: tm.ko
// function: spaDebugGetHashRam @ 0x6f5f0
// size: 124 bytes
//

undefined4 spaDebugGetHashRam(void)

{
  int iVar1;
  undefined2 local_e;
  ushort local_c;
  undefined2 local_a;
  
  iVar1 = 0;
  __memzero(&local_e,6);
  do {
    spa_get_hashram(iVar1,&local_e);
    iVar1 = iVar1 + 1;
    printk("valid= 0x%x, matcharray = 0x%x, action_rsn = 0x%x, action = 0x%x\n",
           ((uint)local_a._1_1_ << 0x1e) >> 0x1f,
           (uint)local_c << 7 | (uint)(local_e._1_1_ >> 1) | (uint)local_a << 0x17,
           ((uint)local_e << 0x17) >> 0x19,(byte)local_e & 3);
  } while (iVar1 != 8);
  return 0;
}

