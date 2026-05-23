// module: mt7915.ko
// function: indicate_rx_pkt @ 0xca9f4
// size: 104 bytes
//

void indicate_rx_pkt(int param_1,int param_2,undefined4 param_3)

{
  uint uVar1;
  
  uVar1 = *(uint *)(param_2 + 0x44);
  if (((uVar1 & 2) != 0) && (*(char *)(param_1 + 0x9daa3) == '\0')) {
    indicate_amsdu_pkt();
    return;
  }
  if ((uVar1 & 0x40) != 0) {
    indicate_eapol_pkt(param_1,param_2,param_3);
    return;
  }
  if ((uVar1 & 0x40000) == 0) {
    indicate_802_11_pkt();
    return;
  }
  indicate_802_3_pkt();
  return;
}

