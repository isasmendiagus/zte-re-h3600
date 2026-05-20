// module: mt7915.ko
// function: mt_serv_set_rdd_on_off @ 0x2516c8
// size: 220 bytes
//

int mt_serv_set_rdd_on_off(undefined4 *param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  
  uVar1 = *(undefined1 *)(param_1 + 0x133);
  puVar3 = (undefined4 *)param_1[0x7c4];
  uVar4 = *param_1;
  printk("%s(): ctrl_band_idx %d, enable %d\n","mt_serv_set_rdd_on_off",uVar1,param_4,param_4);
  if (((code *)*puVar3 == (code *)0x0) ||
     (iVar2 = (*(code *)*puVar3)(uVar4,2,param_4 & 0xff,uVar1), iVar2 == 0)) {
    if ((code *)puVar3[0x4f] == (code *)0x0) {
      iVar2 = 0;
    }
    else {
      (*(code *)puVar3[0x4f])(uVar4,param_2,param_3,param_4);
      iVar2 = 0;
    }
  }
  else {
    printk("%s: op_set_tr_mac, err=0x%08x\n","mt_serv_set_rdd_on_off",iVar2);
    if ((code *)puVar3[0x4f] != (code *)0x0) {
      (*(code *)puVar3[0x4f])(uVar4,param_2,param_3,param_4);
    }
    printk("%s: op_set_rdd_test, err=0x%08x\n","mt_serv_set_rdd_on_off",iVar2);
  }
  return iVar2;
}

