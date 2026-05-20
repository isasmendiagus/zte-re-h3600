// module: bspdriver.ko
// function: ups_i2c_writeb @ 0x10680
// size: 124 bytes
//

undefined4 ups_i2c_writeb(undefined2 param_1,undefined1 param_2,undefined1 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_16;
  undefined1 local_15;
  undefined2 local_14;
  undefined2 local_12;
  undefined2 local_10;
  undefined1 *local_c;
  
  local_16 = param_2;
  local_15 = param_3;
  iVar1 = i2c_get_adapter(1);
  if (iVar1 == 0) {
    printk("<%s>(%d) i2c_bus_num=%d failed !!\n","ups_i2c_writeb",0x2a5,1);
    uVar2 = 0xffffffff;
  }
  else {
    local_10 = 2;
    local_c = &local_16;
    local_12 = 0;
    local_14 = param_1;
    iVar1 = i2c_transfer(iVar1,&local_14,1);
    uVar2 = 0;
    if (iVar1 != 1) {
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

