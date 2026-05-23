// module: tm.ko
// function: zte_api_sw_vlan_get_port_vlancfg @ 0x64440
// size: 224 bytes
//

undefined4 zte_api_sw_vlan_get_port_vlancfg(undefined4 param_1,uint *param_2,uint *param_3)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  int iStack_50;
  int local_4c [11];
  
  piVar3 = &iStack_50;
  __memzero(local_4c,0x2c);
  iVar1 = tm_vlantable_lookup_get(local_4c,param_1);
  if (iVar1 == 0) {
    uVar2 = 0;
    uVar4 = 0;
    uVar5 = 0;
    do {
      piVar3 = piVar3 + 1;
      iVar1 = *piVar3;
      if (iVar1 == 3) {
        uVar4 = uVar4 | 1 << (uVar2 & 0xff);
      }
      else if (iVar1 == 0) {
        printk("not member\n");
      }
      else if (iVar1 == 1) {
        uVar5 = uVar5 | 1 << (uVar2 & 0xff);
      }
      else if (iVar1 == 2) {
        uVar4 = uVar4 | 1 << (uVar2 & 0xff);
      }
      else {
        printk("[%s] L%d attr error!\n","zte_api_sw_vlan_get_port_vlancfg",0x5f2);
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 != 9);
    *param_2 = uVar4;
    *param_3 = uVar5;
    uVar6 = 0;
  }
  else {
    printk("[%s] L%d tm sdk failed!\n","zte_api_sw_vlan_get_port_vlancfg",0x5db);
    uVar6 = 0xffffffff;
  }
  return uVar6;
}

