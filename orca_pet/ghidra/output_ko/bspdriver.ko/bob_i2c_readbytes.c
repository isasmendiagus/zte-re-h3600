// module: bspdriver.ko
// function: bob_i2c_readbytes @ 0x103b0
// size: 256 bytes
//

undefined4 bob_i2c_readbytes(undefined2 param_1,undefined1 param_2,void *param_3,uint param_4)

{
  ushort *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_59;
  undefined2 local_58;
  ushort local_56;
  undefined2 local_54;
  undefined1 *local_50;
  undefined2 local_4c;
  ushort local_4a;
  undefined2 local_48;
  undefined4 *local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_59 = param_2;
  puVar1 = (ushort *)generic_addr_to_client();
  if (puVar1 == (ushort *)0x0 || 0x20 < param_4) {
    uVar3 = 0xffffffff;
  }
  else {
    mutex_lock(&i2cbus_mutex);
    local_50 = &local_59;
    local_48 = (undefined2)param_4;
    local_54 = 1;
    local_56 = *puVar1 & 0x10;
    local_4a = local_56 | 1;
    local_58 = param_1;
    local_4c = param_1;
    local_44 = &local_40;
    iVar2 = i2c_transfer(*(undefined4 *)(puVar1 + 0xc),&local_58,2);
    if (iVar2 == 2) {
      mutex_unlock(&i2cbus_mutex);
      memcpy(param_3,&local_40,param_4);
      uVar3 = 0;
    }
    else {
      mutex_unlock(&i2cbus_mutex);
      uVar3 = 0xffffffff;
    }
  }
  return uVar3;
}

