// module: mt7915.ko
// function: mt_engine_stop @ 0x2556ec
// size: 700 bytes
//

int mt_engine_stop(undefined4 param_1,undefined4 param_2,uint *param_3,undefined4 *param_4,
                  undefined4 param_5,int param_6)

{
  int iVar1;
  undefined1 uVar2;
  uint uVar3;
  uint *puVar4;
  char cVar5;
  undefined4 local_30;
  undefined4 local_2c;
  
  cVar5 = '\0';
  puVar4 = param_3;
  while( true ) {
    if (cVar5 == '\0') {
      uVar2 = 1;
    }
    else {
      uVar2 = 0x24;
    }
    *(undefined1 *)(param_3 + 0x314) = uVar2;
    if ((*puVar4 & 0x101) != 1) {
      printk("%s: test mode has already stopped, ","mt_engine_stop");
      printk("wdev_idx=%u, band_idx=%u\n",(char)puVar4[0xb],cVar5);
      *puVar4 = 0x100;
      return 0;
    }
    iVar1 = (*(code *)param_4[0x5c])(param_1,param_5,cVar5);
    if (iVar1 != 0) goto LAB_002558f0;
    uVar3 = *param_3;
    if ((uVar3 & 0x280) != 0) {
      iVar1 = (*(code *)param_4[0x17])(param_1,0,0,8);
      if (iVar1 != 0) goto LAB_002558f0;
      uVar3 = *param_3 & 0xfffffd7f;
      *param_3 = uVar3;
    }
    if ((uVar3 & 0x200) != 0) {
      iVar1 = (*(code *)param_4[0x17])(param_1,0,0,8);
      if (iVar1 != 0) goto LAB_002558f0;
      *param_3 = *param_3 & 0xfffffdff;
    }
    sys_ad_zero_mem(&local_30,8);
    local_30 = 0x33b86;
    local_2c = (uint)CONCAT11(local_2c._3_1_,cVar5) << 0x10;
    iVar1 = (*(code *)param_4[4])(param_1,0x33b86,local_2c);
    if (iVar1 != 0) goto LAB_002558f0;
    if (param_3[0x33a] != 0) {
      sys_ad_free_mem();
    }
    param_3[0x33a] = 0;
    *(undefined1 *)(param_3 + 0x338) = 0;
    param_3[0x336] = 0;
    param_3[0x337] = 0;
    param_3[0x339] = 1;
    if (puVar4[2] != 0) {
      sys_ad_free_pkt();
      puVar4[2] = 0;
    }
    iVar1 = param_6;
    do {
      if (*(int *)(iVar1 + 0x14) != 0) {
        sys_ad_free_mem();
        *(undefined4 *)(iVar1 + 0x14) = 0;
      }
      iVar1 = iVar1 + 0x18;
    } while (iVar1 != param_6 + 0x48);
    iVar1 = net_ad_release_wdev(param_1,puVar4);
    if (iVar1 != 0) goto LAB_002558f0;
    *param_3 = 0x100;
    iVar1 = (*(code *)param_4[0x16])(param_1);
    if (iVar1 != 0) goto LAB_002558f0;
    if ((code *)param_4[0x35] != (code *)0x0) {
      (*(code *)param_4[0x35])(param_1,1);
    }
    iVar1 = (*(code *)*param_4)(param_1,3,1,cVar5);
    if (iVar1 != 0) goto LAB_002558f0;
    param_3 = param_3 + 0x346;
    if (cVar5 == '\x01') break;
    cVar5 = '\x01';
    puVar4 = puVar4 + 0x346;
  }
  iVar1 = net_ad_enter_normal(param_1,param_2);
  if ((iVar1 == 0) && (iVar1 = net_ad_release_thread(), iVar1 == 0)) {
    printk("%s: leave test mode, wdev_idx=%u\n","mt_engine_stop",(char)puVar4[0xb]);
    return 0;
  }
LAB_002558f0:
  printk("%s: leave test mode fail, err=0x%8x\n","mt_engine_stop",iVar1);
  *puVar4 = 0x100;
  return iVar1;
}

