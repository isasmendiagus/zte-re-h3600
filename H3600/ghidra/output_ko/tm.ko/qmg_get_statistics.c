// module: tm.ko
// function: qmg_get_statistics @ 0x41d18
// size: 356 bytes
//

undefined4 qmg_get_statistics(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14 [2];
  
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(6,&local_28,0,QmgRegTable);
  iVar2 = tmOnuRegRead(7,&local_24,0,QmgRegTable);
  iVar3 = tmOnuRegRead(8,&local_20,0,QmgRegTable);
  iVar4 = tmOnuRegRead(9,&local_1c,0,QmgRegTable);
  iVar5 = tmOnuRegRead(10,&local_18,0,QmgRegTable);
  iVar6 = tmOnuRegRead(0xb,local_14,0,QmgRegTable);
  if (((((iVar2 == 0 && iVar1 == 0) && iVar3 == 0) && iVar4 == 0) && iVar5 == 0) && iVar6 == 0) {
    printk("qmg dn sw fwd     pkt :%u\n",local_28);
    printk("qmg dn hw fwd     pkt :%u\n",local_24);
    printk("qmg dn hw trap    pkt :%u\n",local_20);
    printk("qmg up sw fwd     pkt :%u\n",local_1c);
    printk("qmg up hw fwd     pkt :%u\n",local_18);
    printk("qmg up hw trap    pkt :%u\n",local_14[0]);
    uVar7 = 0;
  }
  else {
    if ((g_tm_debug_level != 0) && (iVar1 = ___ratelimit(_rs_7014,"qmg_get_statistics"), iVar1 != 0)
       ) {
      printk("[TM][qmg_get_statistics]read reg failed!\n");
    }
    uVar7 = 0xffffffff;
  }
  return uVar7;
}

