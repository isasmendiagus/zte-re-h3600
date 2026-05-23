// module: mt7915.ko
// function: set_manual_rdg @ 0xbe200
// size: 204 bytes
//

undefined4 set_manual_rdg(undefined4 param_1,char *param_2)

{
  int iVar1;
  uint local_1c;
  uint local_18;
  undefined4 local_14;
  uint local_10;
  uint local_c;
  
  iVar1 = sscanf(param_2,"%u-%u-%u-%u-%u",&local_1c,&local_18,&local_14,&local_10,&local_c);
  if (iVar1 != 5) {
    if (0 < DebugLevel) {
      printk(
            "Format Error!! should be: iwpriv ra0 set manual_rdg=[init]-[resp]-[txop]-[wcid]-[band]\n"
            );
    }
    return 1;
  }
  if (0 < DebugLevel) {
    printk("\n>> Initiator=%x, Responder=%x, Txop=0x%x, Wcid=%u, BandIdx=%x\n",local_1c,local_18,
           local_14,local_10,local_c);
  }
  AsicSetRDG(param_1,local_10 & 0xffff,local_c & 0xff,local_1c & 0xff,local_18 & 0xff);
  return 1;
}

