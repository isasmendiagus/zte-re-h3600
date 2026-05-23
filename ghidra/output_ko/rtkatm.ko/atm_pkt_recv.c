// module: rtkatm.ko
// function: atm_pkt_recv @ 0x100ec
// size: 120 bytes
//

undefined4 atm_pkt_recv(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  
  puVar2 = cfg;
  bVar1 = *(byte *)(*(int *)(param_1 + 0xcc) + 1);
  if (cfg[(uint)bVar1 * 0xf + 4] != 1) {
    consume_skb();
    return 0xffffffff;
  }
  iVar4 = cfg[(uint)bVar1 * 0xf + 0xe];
  if (iVar4 != 0) {
    uVar3 = *cfg;
    *(undefined4 *)(param_1 + 0x18) = uVar3;
    skb_pull(param_1,2,puVar2,uVar3,param_4);
    (**(code **)(iVar4 + 0x290))(iVar4,param_1);
    return 0;
  }
  return 0xffffffff;
}

