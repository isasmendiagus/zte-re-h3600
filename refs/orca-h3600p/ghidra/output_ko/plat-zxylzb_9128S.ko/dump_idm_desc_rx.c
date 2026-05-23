// module: plat-zxylzb_9128S.ko
// function: dump_idm_desc_rx @ 0x155c4
// size: 80 bytes
//

void dump_idm_desc_rx(undefined4 *param_1)

{
  printk("0x%.8x 0x%.8x:idm %u,len %u ssid %d ssid vld %d\n",*param_1,param_1[1],
         *(byte *)((int)param_1 + 7) >> 7,*(ushort *)(param_1 + 1) & 0x3fff,
         *(byte *)((int)param_1 + 6) & 7,((uint)*(byte *)((int)param_1 + 6) << 0x1c) >> 0x1f);
  return;
}

