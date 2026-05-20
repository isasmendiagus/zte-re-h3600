// module: plat-zxylzb_9128S.ko
// function: cla_ram_dump @ 0x17b4c
// size: 80 bytes
//

undefined4 cla_ram_dump(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  iVar1 = cla_ram_get(param_1,&local_18,param_2);
  if (iVar1 < 0) {
    uVar2 = 0xffffffff;
  }
  else {
    printk("0x%.8x 0x%.8x 0x%.8x 0x%.8x\n",local_18,local_14,local_10,local_c);
    uVar2 = 0;
  }
  return uVar2;
}

