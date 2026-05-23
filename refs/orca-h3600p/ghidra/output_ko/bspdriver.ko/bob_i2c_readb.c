// module: bspdriver.ko
// function: bob_i2c_readb @ 0x100fc
// size: 192 bytes
//

undefined4 bob_i2c_readb(undefined2 param_1,undefined1 param_2,undefined1 *param_3)

{
  ushort *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_35;
  undefined4 local_34;
  undefined2 local_30;
  ushort local_2e;
  undefined2 local_2c;
  undefined1 *local_28;
  undefined2 local_24;
  ushort local_22;
  undefined2 local_20;
  undefined4 *local_1c;
  
  local_34 = 0;
  local_35 = param_2;
  puVar1 = (ushort *)generic_addr_to_client();
  if (puVar1 == (ushort *)0x0) {
    uVar3 = 0xffffffff;
  }
  else {
    mutex_lock(&i2cbus_mutex);
    local_28 = &local_35;
    local_2c = 1;
    local_2e = *puVar1 & 0x10;
    local_20 = 1;
    local_1c = &local_34;
    local_22 = local_2e | 1;
    local_30 = param_1;
    local_24 = param_1;
    iVar2 = i2c_transfer(*(undefined4 *)(puVar1 + 0xc),&local_30,2);
    if (iVar2 == 2) {
      mutex_unlock(&i2cbus_mutex);
      uVar3 = 0;
      *param_3 = (undefined1)local_34;
    }
    else {
      mutex_unlock(&i2cbus_mutex);
      uVar3 = 0xffffffff;
    }
  }
  return uVar3;
}

