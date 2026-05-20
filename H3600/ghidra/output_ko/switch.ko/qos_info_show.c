// module: switch.ko
// function: qos_info_show @ 0x19024
// size: 172 bytes
//

undefined4 qos_info_show(void)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  
  printk("\n***********************QOS INFO********************************\n");
  printk("\nqos mode:%d\n",g_qos_mode);
  printk("\n-----------------------QOS MODE-----------------------------\n");
  printk("\n-----------------------QOS QUEUE-----------------------------\n");
  if (TCONT_QUEUE != 0) {
    puVar1 = &DAT_0002b760;
    iVar2 = 0;
    do {
      iVar3 = iVar2 + 1;
      printk("\nindex;%d,status:%d,qos_weight;%d,weight_flag;%d\n",iVar2,*puVar1,puVar1[-2],
             puVar1[-1]);
      puVar1 = puVar1 + 3;
      iVar2 = iVar3;
    } while (iVar3 < (int)(uint)TCONT_QUEUE);
  }
  printk("\n---------------------------QUEUE-----------------------------\n");
  return 0;
}

