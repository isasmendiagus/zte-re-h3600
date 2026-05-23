// module: mt7915.ko
// function: set_ate_tx_policy @ 0x262174
// size: 444 bytes
//

undefined4 set_ate_tx_policy(undefined4 param_1,char *param_2)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int local_28;
  int local_24 [2];
  
  local_28 = 0;
  local_24[0] = 0;
  if (*param_2 == '\0') {
    if (-1 < DebugLevel) {
      printk("%s: Invalid string\n","set_ate_tx_policy");
    }
  }
  else {
    sscanf(param_2,"%d:%d",&local_28,local_24);
    if (local_28 < 0xd) {
      if (local_24[0] < 2) {
        iVar3 = net_ad_wrap_service(param_1);
        iVar4 = net_ad_wrap_service(param_1);
        iVar2 = DebugLevel;
        *(char *)((uint)*(byte *)(iVar4 + 0x4cc) * 0xd18 + iVar3 + local_28 + 0x6e5) =
             (char)local_24[0];
        if (0 < iVar2) {
          iVar2 = net_ad_wrap_service(param_1);
          uVar1 = *(undefined1 *)(iVar2 + 0x4cc);
          iVar2 = local_28 * 0xf;
          iVar3 = net_ad_wrap_service(param_1);
          iVar4 = net_ad_wrap_service(param_1);
          puVar5 = &_LC58;
          if (*(char *)((uint)*(byte *)(iVar4 + 0x4cc) * 0xd18 + iVar3 + local_28 + 0x6e5) == '\0')
          {
            puVar5 = &_LC59;
          }
          printk("%s: [band%d] Set %s as %s mode.\n","set_ate_tx_policy",uVar1,&DAT_005e1d20 + iVar2
                 ,puVar5);
        }
      }
      else if (-1 < DebugLevel) {
        iVar2 = net_ad_wrap_service(param_1);
        printk("%s: [band%d] Unknown TX policy(%d, 0:TXD ; 1:TXC).\n","set_ate_tx_policy",
               *(undefined1 *)(iVar2 + 0x4cc),local_24[0]);
      }
    }
    else if (-1 < DebugLevel) {
      iVar2 = net_ad_wrap_service(param_1);
      printk("%s: [band%d] Unknown TX mode(%d).\n","set_ate_tx_policy",
             *(undefined1 *)(iVar2 + 0x4cc),local_28);
    }
  }
  return 1;
}

