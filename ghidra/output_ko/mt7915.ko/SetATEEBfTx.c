// module: mt7915.ko
// function: SetATEEBfTx @ 0x2682bc
// size: 592 bytes
//

undefined4 SetATEEBfTx(int param_1,char *param_2)

{
  undefined1 uVar1;
  int iVar2;
  size_t sVar3;
  undefined *puVar4;
  char cVar5;
  undefined4 uVar6;
  uint uVar7;
  bool bVar8;
  
  iVar2 = net_ad_wrap_service();
  uVar7 = (uint)*(byte *)(iVar2 + 0x4cc);
  if (param_2 == (char *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s: No parameters!!\n","SetATEEBfTx");
    }
  }
  else {
    sVar3 = strlen(param_2);
    if (sVar3 == 1) {
      iVar2 = rstrtok(param_2,&_LC2);
      uVar6 = 1;
      if (iVar2 == 0) {
        uVar1 = 0;
      }
      else {
        uVar1 = 0;
        cVar5 = '\0';
        do {
          if (cVar5 == '\0') {
            uVar1 = simple_strtol(iVar2,0,10);
            iVar2 = rstrtok(0,&_LC2);
            cVar5 = '\x01';
            if (iVar2 == 0) break;
          }
          uVar6 = 0;
          if (-1 < DebugLevel) {
            printk("%s: Set wrong parameters\n","SetATEEBfTx");
          }
          cVar5 = cVar5 + '\x01';
          iVar2 = rstrtok(0,&_LC2);
        } while (iVar2 != 0);
      }
      iVar2 = net_ad_wrap_service(param_1);
      bVar8 = -1 < DebugLevel;
      *(undefined1 *)(iVar2 + uVar7 * 0xd18 + 0x11cd) = uVar1;
      if (bVar8) {
        iVar2 = net_ad_wrap_service(param_1);
        printk("%s: band[%d] eTxBf = %d !!!!!\n","SetATEEBfTx",uVar7,
               *(undefined1 *)(iVar2 + uVar7 * 0xd18 + 0x11cd));
      }
      *(undefined2 *)(param_1 + 0xa3b008) = 1;
      *(undefined2 *)(param_1 + 0xa3b012) = 0x1111;
      *(undefined4 *)(param_1 + 0xa3b00e) = 0x11111100;
      iVar2 = net_ad_wrap_service(param_1);
      if (*(char *)(uVar7 * 0xd18 + iVar2 + 0x11cd) == '\0') {
        puVar4 = &_LC326;
      }
      else {
        puVar4 = &_LC332;
      }
      SetATESpeIdx(param_1,puVar4);
      iVar2 = net_ad_wrap_service(param_1);
      MT_ATEComposePkt(param_1,*(undefined4 *)(uVar7 * 0xd18 + iVar2 + 0x4e4),uVar7,0);
      return uVar6;
    }
    if (-1 < DebugLevel) {
      printk("%s: Wrong parameter format!!\n","SetATEEBfTx");
    }
  }
  return 0;
}

