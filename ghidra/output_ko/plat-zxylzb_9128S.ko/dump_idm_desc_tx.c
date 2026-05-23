// module: plat-zxylzb_9128S.ko
// function: dump_idm_desc_tx @ 0x15e68
// size: 64 bytes
//

void dump_idm_desc_tx(undefined4 *param_1)

{
  printk("0x%.8x 0x%.8x:idm %u,len %u ssid %d\n",*param_1,param_1[1],
         *(byte *)((int)param_1 + 7) >> 7,*(ushort *)(param_1 + 1) & 0x3fff,
         ((uint)*(byte *)((int)param_1 + 7) << 0x19) >> 0x1d);
  return;
}

