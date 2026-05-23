// module: bspdriver.ko
// function: ups_i2c_readb @ 0x10828
// size: 188 bytes
//

undefined4 ups_i2c_readb(undefined2 param_1,undefined1 param_2,undefined1 *param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_35;
  undefined1 local_34 [4];
  undefined2 local_30;
  undefined2 local_2e;
  undefined2 local_2c;
  undefined1 *local_28;
  undefined2 local_24;
  undefined2 local_22;
  undefined2 local_20;
  undefined1 *local_1c;
  
  local_35 = param_2;
  iVar1 = i2c_get_adapter(1);
  if (iVar1 == 0) {
    printk("<%s>(%d) i2c_bus_num=%d failed !!\n","ups_i2c_readb",0x27a,1);
    uVar2 = 0xffffffff;
  }
  else {
    __memzero(&local_30,0x18);
    __memzero(local_34,4);
    local_28 = &local_35;
    local_2e = 0;
    local_2c = 1;
    local_22 = 1;
    local_20 = 1;
    local_30 = param_1;
    local_24 = param_1;
    local_1c = local_34;
    iVar1 = i2c_transfer(iVar1,&local_30,2);
    if (iVar1 == 2) {
      uVar2 = 0;
      *param_3 = local_34[0];
    }
    else {
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

