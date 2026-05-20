// module: mt7915.ko
// function: ap_set_rfeature_he_gi @ 0xcee60
// size: 252 bytes
//

void ap_set_rfeature_he_gi(int param_1,byte *param_2)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  bool bVar6;
  undefined2 local_1b;
  undefined1 local_19;
  
  local_1b = 0x5500;
  local_19 = 0xaa;
  bVar1 = *param_2;
  if (0 < DebugLevel) {
    printk("func:%s, arg:%d \n","ap_set_rfeature_he_gi",(uint)bVar1);
  }
  uVar2 = HcGetMaxStaNum(param_1);
  puVar5 = (uint *)(param_1 + 0xa1d20);
  for (uVar4 = 0; (uVar3 = HcGetMaxStaNum(param_1), uVar4 < uVar3 && (uVar4 <= uVar2));
      uVar4 = uVar4 + 1) {
    uVar3 = *puVar5;
    bVar6 = puVar5 != (uint *)0x0;
    puVar5 = puVar5 + 0x530;
    if ((bVar6 && (uVar3 & 0xfffffbff) != 0) && (uVar3 == 2 || (uVar3 - 0x20001 & 0xfffdffff) == 0))
    {
      snd_ra_fw_cmd(0xb,param_1,uVar4,(int)&local_1b + (uint)bVar1);
    }
  }
  return;
}

