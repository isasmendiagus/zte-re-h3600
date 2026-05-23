// module: tm.ko
// function: spaDebugGetMatchRam @ 0x6f408
// size: 488 bytes
//

undefined4 spaDebugGetMatchRam(void)

{
  uint uVar1;
  int iVar2;
  undefined2 local_3f;
  undefined2 local_3d;
  byte local_3b;
  byte local_3a;
  byte local_39;
  byte local_38;
  byte local_37;
  byte local_36;
  byte local_35;
  byte local_34;
  byte local_33;
  byte local_32;
  byte local_31;
  byte local_30;
  byte local_2f;
  byte local_2e;
  byte local_2d;
  byte local_2c;
  byte local_2b;
  byte local_2a;
  byte local_29;
  
  iVar2 = 0;
  __memzero(&local_3f,0x17);
  do {
    spa_get_matchram(iVar2,&local_3f);
    printk("ram addr:%d\n",iVar2);
    iVar2 = iVar2 + 1;
    uVar1 = (uint)local_29;
    printk("valid0= %d, v4_v6_flag0 = %d, offset_mode0 = %d, offset0 = 0x%x, compare_mode = 0x%x,  mask= 0x%04x, data = 0x%x\n"
           ,(uVar1 << 0x1c) >> 0x1f,(uVar1 << 0x1d) >> 0x1e,(uVar1 & 1) << 1 | (uint)(local_2a >> 7)
           ,((uint)local_2a << 0x19) >> 0x1a,(local_2a & 1) << 1 | (uint)(local_2b >> 7),
           (uint)local_2c << 1 | (uint)(local_2d >> 7) | (local_2b & 0x7f) << 9,
           (uint)local_2e << 1 | (uint)(local_2f >> 7) | (local_2d & 0x7f) << 9);
    uVar1 = (uint)local_2f;
    printk("valid1= %d, v4_v6_flag1 = %d, offset_mode1 = %d, offset1 = 0x%x,compare_mode1 = 0x%x,  mask1= 0x%04x, data1 = 0x%x\n"
           ,(uVar1 << 0x19) >> 0x1f,(uVar1 << 0x1a) >> 0x1e,(uVar1 << 0x1c) >> 0x1e,
           (uVar1 & 3) << 4 | (uint)(local_30 >> 4),((uint)local_30 << 0x1c) >> 0x1e,
           (uint)local_31 << 6 | (uint)(local_32 >> 2) | (local_30 & 3) << 0xe,
           (uint)local_33 << 6 | (uint)(local_34 >> 2) | (local_32 & 3) << 0xe);
    printk("valid2= %d, v4_v6_flag2 = %d, offset_mode2 = %d, offset2 = 0x%x,compare_mode2 = 0x%x,  mask2= 0x%04x, data2 = 0x%x\n"
           ,((uint)local_34 << 0x1e) >> 0x1f,(local_34 & 1) << 1 | (uint)(local_35 >> 7),
           ((uint)local_35 << 0x19) >> 0x1e,(local_35 & 0x1f) << 1 | (uint)(local_36 >> 7),
           ((uint)local_36 << 0x19) >> 0x1e,
           (uint)local_37 << 3 | (uint)(local_38 >> 5) | (local_36 & 0x1f) << 0xb,
           (uint)local_39 << 3 | (uint)(local_3a >> 5) | (local_38 & 0x1f) << 0xb);
    uVar1 = (uint)local_3a;
    printk("valid3= %d, v4_v6_flag3 = %d, offset_mode3 = %d, offset3 = 0x%x,compare_mode3 = 0x%x,  mask3= 0x%04x, data3 = 0x%x\n"
           ,(uVar1 << 0x1b) >> 0x1f,(uVar1 << 0x1c) >> 0x1e,uVar1 & 3,local_3b >> 2,local_3b & 3,
           local_3d,local_3f);
  } while (iVar2 != 8);
  return 0;
}

