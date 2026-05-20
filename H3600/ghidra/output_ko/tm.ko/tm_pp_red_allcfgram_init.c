// module: tm.ko
// function: tm_pp_red_allcfgram_init @ 0x45e2c
// size: 144 bytes
//

void tm_pp_red_allcfgram_init(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  __memzero(&local_3c,0x24);
  uVar4 = 0;
  iVar2 = 0;
  do {
    local_3c = 0x3fff;
    iVar3 = iVar2 + 1;
    local_28 = 0x80;
    local_24 = 0x100;
    local_20 = 0xffff;
    local_1c = 0xffff;
    local_38 = 0xff;
    local_34 = 0xff;
    local_30 = 0xff;
    local_2c = 0xff;
    uVar1 = red_set_buffer_queue_cfg(iVar2,&local_3c);
    uVar4 = uVar4 | uVar1;
    iVar2 = iVar3;
  } while (iVar3 != 0x180);
  if (uVar4 != 0) {
    printk("-----tm_pp_red_allcfgram_init faild----\n");
  }
  return;
}

