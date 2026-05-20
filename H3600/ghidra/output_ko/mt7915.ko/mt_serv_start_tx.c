// module: mt7915.ko
// function: mt_serv_start_tx @ 0x250dc0
// size: 264 bytes
//

int mt_serv_start_tx(undefined4 *param_1)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = (uint)*(byte *)(param_1 + 0x133);
  if ((((*(char *)(param_1 + uVar2 * 0x346 + 0x44e) == ' ') &&
       (*(char *)((int)param_1 + uVar2 * 0xd18 + 0x1137) != '\x01')) &&
      (*(char *)((int)param_1 + uVar2 * 0xd18 + 0x1136) != '\x01')) &&
     (*(byte *)((int)param_1 + uVar2 * 0xd18 + 0x1135) < 8)) {
    iVar1 = 0x204;
    printk("%s: bandwidth must to be 40MHz,\n","mt_serv_start_tx");
    printk("\t\t due to MCS32 imply 40MHz MCS0\n");
  }
  else {
    if (*(char *)(param_1 + 0x7d1) == '\0') {
      iVar1 = mt_engine_calc_ipg_param_by_ipg(param_1 + uVar2 * 0x346 + 0x138);
      if (iVar1 != 0) goto LAB_00250e10;
      iVar1 = mt_engine_start_tx(*param_1,param_1 + uVar2 * 0x346 + 0x138,param_1[0x7c4],uVar2);
    }
    else {
      iVar1 = (**(code **)(param_1[0x7c4] + 0x68))(*param_1,uVar2,param_1 + uVar2 * 0x346 + 0x138);
    }
    if (iVar1 == 0) {
      return 0;
    }
  }
LAB_00250e10:
  printk("%s: err=0x%08x\n","mt_serv_start_tx",iVar1);
  return iVar1;
}

