// module: mt7915.ko
// function: sta_set_rfeature_gi @ 0xceaf8
// size: 120 bytes
//

void sta_set_rfeature_gi(undefined4 param_1,byte *param_2)

{
  byte bVar1;
  undefined2 local_b;
  undefined1 local_9;
  
  local_b = 0x5500;
  local_9 = 0xaa;
  bVar1 = *param_2;
  if (0 < DebugLevel) {
    printk("func:%s, arg:%d\n","sta_set_rfeature_gi",(uint)bVar1);
  }
  snd_ra_fw_cmd(0xb,param_1,1,(int)&local_b + (uint)bVar1);
  return;
}

