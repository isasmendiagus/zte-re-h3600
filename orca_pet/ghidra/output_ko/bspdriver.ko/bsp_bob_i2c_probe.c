// module: bspdriver.ko
// function: bsp_bob_i2c_probe @ 0x101bc
// size: 224 bytes
//

undefined4 bsp_bob_i2c_probe(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  uint uVar4;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  if (param_2 == 0x28 && param_3 != 0) {
    uVar4 = param_3 + 0x28U & 0xff;
    if (uVar4 < 0x29) goto LAB_00010260;
  }
  else {
    uVar4 = 0x38;
  }
  uVar2 = 0x28;
  puVar3 = &local_38;
  do {
    iVar1 = bob_i2c_readb(param_1,uVar2,puVar3);
    if (iVar1 < 0) {
      if (uVar2 < uVar4) {
        printk("i2c_probe(0x%02x) failed.\n",param_1);
        return 0xffffffff;
      }
      break;
    }
    uVar2 = uVar2 + 1 & 0xff;
    puVar3 = (undefined4 *)((int)puVar3 + 1);
  } while (uVar2 < uVar4);
LAB_00010260:
  printk("%s found.\n",&local_38);
  return 0;
}

