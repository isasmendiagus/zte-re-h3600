// module: bspdriver.ko
// function: bob_i2c_writeb @ 0x10344
// size: 108 bytes
//

undefined4 bob_i2c_writeb(undefined4 param_1,undefined1 param_2,undefined1 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_a;
  undefined1 local_9;
  
  local_a = param_2;
  local_9 = param_3;
  iVar1 = generic_addr_to_client();
  if (iVar1 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    mutex_lock(&i2cbus_mutex);
    iVar1 = i2c_master_send(iVar1,&local_a,2);
    if (iVar1 == 2) {
      mutex_unlock(&i2cbus_mutex);
      uVar2 = 0;
    }
    else {
      mutex_unlock(&i2cbus_mutex);
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

