// module: plat-zxylzb_9128S.ko
// function: pon_pp_brg_int @ 0x174f4
// size: 708 bytes
//

void pon_pp_brg_int(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  undefined1 uStack_27;
  
  uVar3 = *(uint *)(pp_base + 0x8054) & ~*(uint *)(pp_base + 0x8050);
  if ((uVar3 & 1) != 0) {
    uVar1 = *(uint *)(pp_base + 0x8060);
    uVar2 = *(uint *)(pp_base + 0x8064);
    printk("port migrate:pbm %d to pbm %d vlan %d mac %.2x %.2x %.2x %.2x %.2x %.2x\n",
           *(uint *)(pp_base + 0x8068) & 0xff,(*(uint *)(pp_base + 0x8068) << 0x10) >> 0x18,
           uVar2 >> 0x10 & 0xfff,uVar2 >> 8 & 0xff,uVar2 & 0xff,uVar1 >> 0x18,uVar1 >> 0x10 & 0xff,
           uVar1 >> 8 & 0xff,uVar1 & 0xff);
    *(undefined4 *)(pp_base + 0x8068) = 0;
  }
  if ((uVar3 & 2) != 0) {
    uVar1 = *(uint *)(pp_base + 0x80a8);
    uVar2 = *(uint *)(pp_base + 0x80ac);
    uStack_27 = (undefined1)(uVar2 >> 8);
    printk("mac learn:pbm %d vlan %d mac %.2x %.2x %.2x %.2x %.2x %.2x\n",
           *(uint *)(pp_base + 0x80b0) & 0xff,uVar2 >> 0x10 & 0xfff,uStack_27,uVar2 & 0xff,
           uVar1 >> 0x18,uVar1 >> 0x10 & 0xff,uVar1 >> 8 & 0xff,uVar1 & 0xff);
    *(undefined4 *)(pp_base + 0x80b0) = 0;
  }
  if ((uVar3 & 4) != 0) {
    uVar1 = *(uint *)(pp_base + 0x80f0);
    uVar2 = *(uint *)(pp_base + 0x80f4);
    uStack_27 = (undefined1)(uVar2 >> 8);
    printk("hash collision:pbm %d vlan %d mac %.2x %.2x %.2x %.2x %.2x %.2x\n",
           *(uint *)(pp_base + 0x80f8) & 0xff,uVar2 >> 0x10 & 0xfff,uStack_27,uVar2 & 0xff,
           uVar1 >> 0x18,uVar1 >> 0x10 & 0xff,uVar1 >> 8 & 0xff,uVar1 & 0xff);
    *(undefined4 *)(pp_base + 0x80f8) = 0;
  }
  if ((uVar3 & 8) != 0) {
    uVar3 = *(uint *)(pp_base + 0x8138);
    uVar1 = *(uint *)(pp_base + 0x813c);
    uStack_27 = (undefined1)(uVar1 >> 8);
    printk("mac aged:pbm %d vlan %d mac %.2x %.2x %.2x %.2x %.2x %.2x\n",
           *(uint *)(pp_base + 0x8140) & 0xff,uVar1 >> 0x10 & 0xfff,uStack_27,uVar1 & 0xff,
           uVar3 >> 0x18,uVar3 >> 0x10 & 0xff,uVar3 >> 8 & 0xff,uVar3 & 0xff);
    *(undefined4 *)(pp_base + 0x8140) = 0;
  }
  return;
}

