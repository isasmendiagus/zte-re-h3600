// module: bspdriver.ko
// function: bob_i2c_writebytes @ 0x1075c
// size: 200 bytes
//

undefined4 bob_i2c_writebytes(undefined4 param_1,undefined1 param_2,void *param_3,uint param_4)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined1 local_39;
  undefined1 auStack_38 [36];
  
  memset(&local_39,0,0x21);
  local_39 = param_2;
  if (param_4 < 0x21) {
    memcpy(auStack_38,param_3,param_4);
    iVar1 = generic_addr_to_client(param_1);
    uVar4 = param_4 + 1 & 0xffff;
    if (iVar1 == 0) {
      uVar3 = 0xffffffff;
    }
    else {
      mutex_lock(&i2cbus_mutex);
      uVar2 = i2c_master_send(iVar1,&local_39,uVar4);
      if (uVar4 == uVar2) {
        mutex_unlock(&i2cbus_mutex);
        uVar3 = 0;
      }
      else {
        mutex_unlock(&i2cbus_mutex);
        uVar3 = 0xffffffff;
      }
    }
  }
  else {
    printk("<%s>(%d):write length out of range!\n","bob_i2c_writebytes",0x229);
    uVar3 = 0xffffffff;
  }
  return uVar3;
}

