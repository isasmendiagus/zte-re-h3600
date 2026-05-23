// module: mt7915.ko
// function: set_txbf_dsnr_write @ 0xe80f0
// size: 244 bytes
//

undefined4 set_txbf_dsnr_write(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 uStack_3c;
  undefined4 local_38 [9];
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  os_zero_mem(local_38,0x20);
  iVar2 = rstrtok(param_2,&_LC232);
  if (iVar2 == 0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("Error: Un-expected format!\n");
    uVar3 = 0;
  }
  else {
    uVar3 = os_str_toul(iVar2,0,0x10);
    iVar2 = rstrtok(0,&_LC232);
    if (iVar2 != 0) {
      puVar5 = &uStack_3c;
      do {
        uVar4 = os_str_toul(iVar2,0,0x10);
        puVar5 = puVar5 + 1;
        *puVar5 = uVar4;
        iVar2 = rstrtok(0,&_LC232);
      } while (iVar2 != 0);
    }
    if (*(code **)(iVar1 + 0x170) == (code *)0x0) {
      return 0;
    }
    uVar3 = (**(code **)(iVar1 + 0x170))(*(undefined4 *)(param_1 + 0xa797a0),uVar3,local_38);
  }
  return uVar3;
}

