// module: plat-zxylzb_9128S.ko
// function: dump_desc @ 0x19894
// size: 100 bytes
//

void dump_desc(undefined4 *param_1)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = *(byte *)((int)param_1 + 7);
  bVar2 = *(byte *)(param_1 + 2);
  printk("0x%.8x 0x%.8x 0x%.8x 0x%.8x 0x%.8x\n",param_1,*param_1,param_1[1],param_1[2],param_1[3]);
  printk("bp %u gem %u len %u \n",(uint)(bVar1 >> 1) | (uint)bVar2 << 7,
         *(ushort *)(param_1 + 1) & 0xfff,*(ushort *)(param_1 + 3) >> 2);
  return;
}

