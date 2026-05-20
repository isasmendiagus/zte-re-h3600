// module: mt7915.ko
// function: mt_engine_start_rx @ 0x256bbc
// size: 880 bytes
//

int mt_engine_start_rx(int param_1,uint *param_2,undefined4 *param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  uint uVar5;
  uint *puVar6;
  uint *puVar7;
  byte bVar8;
  uint uVar9;
  
  uVar5 = *param_2;
  if ((uVar5 & 4) == 0) {
    iVar1 = net_ad_set_device_info(param_1,param_2,(int)param_2 + 0x111,param_4,1);
    if ((iVar1 == 0) &&
       (((((uVar5 & 2) == 0 || (iVar1 = (*(code *)*param_3)(param_1,1,0,param_4), iVar1 == 0)) &&
         (iVar1 = (*(code *)param_3[0x5a])(param_1,param_4,(short)param_2[800]), iVar1 == 0)) &&
        (iVar1 = (*(code *)*param_3)(param_1,6,0,param_4), iVar1 == 0)))) {
      net_ad_cfg_queue(param_1,0);
      net_ad_cfg_queue(param_1,1);
      if ((((((uVar5 & 2) == 0) || (iVar1 = (*(code *)*param_3)(param_1,1,1,param_4), iVar1 == 0))
           && (iVar1 = (*(code *)*param_3)(param_1,6,1,param_4), iVar1 == 0)) &&
          ((iVar1 = (*(code *)param_3[0x13])(param_1,0,0), iVar1 == 0 &&
           (iVar1 = (*(code *)param_3[0x13])(param_1,1,0), iVar1 == 0)))) &&
         ((*(char *)(param_1 + 0x34) == '\0' ||
          ((iVar1 = (*(code *)param_3[0x13])(param_1,0,1), iVar1 == 0 &&
           (iVar1 = (*(code *)param_3[0x13])(param_1,1,1), iVar1 == 0)))))) {
        *param_2 = uVar5 | 4;
        if (*(char *)((int)param_2 + 0xc55) != '\n') {
          if (*(char *)((int)param_2 + 0xc55) != '\v') {
            return 0;
          }
          if (param_2[0x30c] == 0) {
            uVar5 = 0xf800;
          }
          else {
            uVar5 = param_2[0x30c] & 0xffff;
          }
          (*(code *)param_3[0x53])(param_1,param_4,uVar5);
          return 0;
        }
        puVar4 = param_2 + 0x14f;
        puVar6 = puVar4;
        do {
          while ((char)*puVar6 == '\0') {
            puVar6 = puVar6 + 0x1b;
            if (puVar6 == param_2 + 0x2ff) goto LAB_00256e0c;
          }
          puVar7 = puVar6 + 0x1b;
          mt_engine_calc_phy(puVar6,puVar6[8] + 0xd,*(undefined1 *)((int)param_2 + 0xc5a),
                             (char)param_2[0x317],((byte)param_2[0x31c] & 0x7f) << 1);
          puVar6 = puVar7;
        } while (puVar7 != param_2 + 0x2ff);
LAB_00256e0c:
        uVar9 = 0;
        uVar3 = 0;
        uVar5 = 0;
        puVar6 = puVar4;
        do {
          uVar2 = uVar9 & 0xff;
          uVar9 = uVar9 + 1;
          if (((char)*puVar6 != '\0') && (uVar5 < puVar6[0x18])) {
            uVar5 = puVar6[0x18];
            uVar3 = uVar2;
          }
          puVar6 = puVar6 + 0x1b;
        } while (uVar9 != 0x10);
        if (uVar3 < 0x10) {
          *(char *)(param_2 + 0x2ff) = (char)uVar3;
          printk("%s: dominated by user[%d], RU index:%d\n","mt_engine_search_dom_ru",uVar3,
                 (param_2 + uVar3 * 0x1b)[0x152] >> 1);
          if (param_2 + uVar3 * 0x1b != (uint *)0xfffffac4) {
            bVar8 = *(byte *)((int)param_2 + 0xc57);
            if (2 < bVar8) {
              bVar8 = 3;
            }
            (*(code *)param_3[0x52])
                      (param_1,param_4,3,1,bVar8,(char)param_2[0x317],
                       *(undefined1 *)((int)param_2 + 0xc5a),(char)param_2[0x2ff],puVar4);
            return 0;
          }
          iVar1 = 0x300;
        }
        else {
          iVar1 = 0x300;
          printk("%s: invalid user index:%d\n","mt_engine_search_dom_ru");
        }
      }
    }
    printk("%s: err=0x%08x\n","mt_engine_start_rx",iVar1);
  }
  else {
    iVar1 = 0;
    printk("%s: already in RXFRAME mode now, rx is ongoing!\n","mt_engine_start_rx");
  }
  return iVar1;
}

