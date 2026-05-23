// module: mt7915.ko
// function: mt_serv_tx_power_operation @ 0x25134c
// size: 288 bytes
//

int mt_serv_tx_power_operation(undefined4 *param_1,undefined4 param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 *puVar5;
  
  uVar1 = (uint)*(byte *)(param_1 + 0x133);
  uVar3 = *param_1;
  iVar2 = param_1[0x7c4];
  puVar5 = param_1 + uVar1 * 0x346 + 0x138;
  if ((puVar5 == (undefined4 *)0x0) || (param_1 + uVar1 * 0x346 == (undefined4 *)0xffffee9c)) {
    return 0x201;
  }
  uVar4 = param_1[uVar1 * 0x346 + 0x459];
  if (uVar4 < 4) {
    switch(param_2) {
    case 0:
      *(char *)((int)param_1 + uVar4 + uVar1 * 0xd18 + 0x1178) =
           (char)param_1[uVar1 * 0x346 + 0x45a];
      iVar2 = (**(code **)(iVar2 + 0xe8))(uVar3,puVar5);
      break;
    case 1:
      iVar2 = (**(code **)(iVar2 + 0xe4))
                        (uVar3,puVar5,uVar1,*(undefined1 *)(param_1 + uVar1 * 0x346 + 0x44c),
                         uVar4 & 0xff,param_1 + uVar1 * 0x346 + 0x45a);
      break;
    case 2:
    case 3:
      return 0;
    default:
      goto switchD_002513c4_default;
    }
    if (iVar2 != 0) {
      printk("%s: err=0x%08x\n","mt_serv_tx_power_operation",iVar2);
    }
  }
  else {
switchD_002513c4_default:
    iVar2 = 0x204;
  }
  return iVar2;
}

