// module: plat-zxylzb_9128S.ko
// function: dump_mac_data @ 0x16918
// size: 148 bytes
//

void dump_mac_data(undefined4 param_1,undefined4 param_2,undefined1 *param_3)

{
  undefined1 uVar1;
  undefined4 uVar2;
  
  printk("depth %u id %u\n",param_1,param_2);
  uVar1 = *param_3;
  uVar2 = get_mac_status((byte)param_3[8] >> 4);
  printk("\tpbm %x \"%s\" vlan:%d mac:%.2x %.2x %.2x %.2x %.2x %.2x\n",uVar1,uVar2,
         (uint)(byte)param_3[7] | ((byte)param_3[8] & 0xf) << 8,param_3[6],param_3[5],param_3[4],
         param_3[3],param_3[2],param_3[1]);
  return;
}

