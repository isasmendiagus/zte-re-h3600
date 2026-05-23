// module: plat-zxylzb_9128S.ko
// function: dump_desc_tx @ 0x19510
// size: 108 bytes
//

void dump_desc_tx(undefined4 *param_1)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = *(byte *)((int)param_1 + 7);
  bVar2 = *(byte *)(param_1 + 2);
  printk("0x%.8x:0x%.8x 0x%.8x 0x%.8x 0x%.8x\n",param_1,*param_1,param_1[1],param_1[2],param_1[3]);
  printk("bp %u gem %u len %u oam_omci_Flag %u\n",(uint)(bVar1 >> 1) | (uint)bVar2 << 7,
         *(undefined2 *)(param_1 + 1),*(ushort *)(param_1 + 3) >> 2,
         ((uint)*(byte *)((int)param_1 + 6) << 0x1d) >> 0x1f);
  return;
}

