// module: mt7915.ko
// function: set_txbf_angle_write @ 0xe7fd4
// size: 284 bytes
//

undefined4 set_txbf_angle_write(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  undefined4 uStack_54;
  undefined4 local_50 [14];
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  os_zero_mem(local_50,0x38);
  iVar2 = rstrtok(param_2,&_LC232);
  if (iVar2 != 0) {
    uVar3 = os_str_toul(iVar2,0,0x10);
    iVar2 = rstrtok(0,&_LC232);
    if (iVar2 != 0) {
      uVar4 = os_str_toul(iVar2,0,0x10);
      iVar2 = rstrtok(0,&_LC232);
      if (iVar2 != 0) {
        puVar6 = &uStack_54;
        do {
          uVar5 = os_str_toul(iVar2,0,0x10);
          puVar6 = puVar6 + 1;
          *puVar6 = uVar5;
          iVar2 = rstrtok(0,&_LC232);
        } while (iVar2 != 0);
      }
      if (*(code **)(iVar1 + 0x16c) == (code *)0x0) {
        return 0;
      }
      uVar3 = (**(code **)(iVar1 + 0x16c))(*(undefined4 *)(param_1 + 0xa797a0),uVar3,uVar4,local_50)
      ;
      return uVar3;
    }
  }
  if (-1 < DebugLevel) {
    printk("Error: Un-expected format!\n");
  }
  return 0;
}

