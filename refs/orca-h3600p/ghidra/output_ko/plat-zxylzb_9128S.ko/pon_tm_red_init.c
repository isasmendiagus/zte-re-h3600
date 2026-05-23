// module: plat-zxylzb_9128S.ko
// function: pon_tm_red_init @ 0x1af78
// size: 316 bytes
//

undefined4 pon_tm_red_init(void)

{
  int iVar1;
  uint uVar2;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  uVar2 = 0;
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  local_18 = 0x400;
  do {
    iVar1 = red_set_queue_cfg(uVar2 & 0xffff,&local_18,0);
    if (iVar1 < 0) goto LAB_0001b09c;
    uVar2 = uVar2 + 1;
  } while (uVar2 != 0x10);
  local_18 = 0x800400;
  do {
    iVar1 = red_set_queue_cfg(uVar2 & 0xffff,&local_18,0);
    if (iVar1 < 0) {
LAB_0001b09c:
      printk("red queue %d cfg failed,%d\n",uVar2);
      return 0xffffffff;
    }
    uVar2 = uVar2 + 1;
  } while (uVar2 != 400);
  uVar2 = 0;
  local_18 = 0x200020;
  do {
    iVar1 = red_set_queue_cfg(uVar2 & 0xffff,&local_18,2);
    if (iVar1 < 0) goto LAB_0001b084;
    uVar2 = uVar2 + 1;
  } while (uVar2 != 0x180);
  uVar2 = 0;
  local_14 = 0x100ff80;
  local_18 = 0xff803fff;
  local_10 = 0x100200;
  local_c = 0x20;
  while (iVar1 = red_set_queue_cfg(uVar2 & 0xffff,&local_18,4), -1 < iVar1) {
    uVar2 = uVar2 + 1;
    if (uVar2 == 0x180) {
      return 0;
    }
  }
LAB_0001b084:
  printk("red queue %d cfg ram 0 failed,%d\n",uVar2);
  return 0xffffffff;
}

