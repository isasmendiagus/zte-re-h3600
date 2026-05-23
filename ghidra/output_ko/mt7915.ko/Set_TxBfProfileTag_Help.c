// module: mt7915.ko
// function: Set_TxBfProfileTag_Help @ 0xe7048
// size: 48 bytes
//

undefined4 Set_TxBfProfileTag_Help(void)

{
  if (0 < DebugLevel) {
    printk(
          "========================================================================================================================\nTxBfProfile Tag1 setting example :\niwpriv ra0 set TxBfProfileTagPfmuIdx  =xx\niwpriv ra0 set TxBfProfileTagBfType   =xx (0: iBF; 1: eBF)\niwpriv ra0 set TxBfProfileTagBw       =xx (0/1/2/3 : BW20/40/80/160NC)\niwpriv ra0 set TxBfProfileTagSuMu     =xx (0:SU, 1:MU)\niwpriv ra0 set TxBfProfileTagInvalid  =xx (0: valid, 1: invalid)\niwpriv ra0 set TxBfProfileTagMemAlloc =xx:xx:xx:xx:xx:xx:xx:xx (mem_row, mem_col), ..\niwpriv ra0 set TxBfProfileTagMatrix   =nrow:nol:ng:LM\niwpriv ra0 set TxBfProfileTagSnr      =SNR_STS0:SNR_STS1:SNR_STS2:SNR_STS3\n\n\nTxBfProfile Tag2 setting example :\niwpriv ra0 set TxBfProfileTagSmtAnt   =xx (11:0)\niwpriv ra0 set TxBfProfileTagSeIdx    =xx\niwpriv ra0 set TxBfProfileTagRmsdThrd =xx\niwpriv ra0 set TxBfProfileTagMcsThrd  =xx:xx:xx:xx:xx:xx (MCS TH L1SS:S1SS:L2SS:....)\niwpriv ra0 set TxBfProfileTagTimeOut  =xx\niwpriv ra0 set TxBfProfileTagDesiredBw=xx (0/1/2/3 : BW20/40/80/160NC)\niwpriv ra0 set TxBfProfileTagDesiredNc=xx\niwpriv ra0 set TxBfProfileTagDesiredNr=xx\n\n\nRead TxBf profile Tag :\niwpriv ra0 set TxBfProfileTagRead     =xx (PFMU ID)\n\nWrite TxBf profile Tag :\niwpriv ra0 set TxBfProfileTagWrite    =xx (PFMU ID)\nWhen you use one of relative CMD to update one of tag parameters, you should call TxBfProfileTagWrite to update Tag\n\n\nRead TxBf profile Data\t:\niwpriv ra0 set TxBfProfileDataRead    =xx (PFMU ID)\n\nWrite TxBf profile Data :\niwpriv ra0 set TxBfProfileDataWrite   =BW :subcarrier:phi11:psi2l:Phi21:Psi31:Phi31:Psi41:Phi22:Psi32:Phi32:Psi42:Phi33:Psi43\niwpriv ra0 set TxBfProfileDataWriteAll=Profile ID : BW (BW       : 0x00 (20M) , 0x01 (40M), 0x02 (80M), 0x3 (160M)\nWhen you use CMD TxBfProfileDataWrite to update profile data per subcarrier, you should call TxBfProfileDataWriteAll to update all of\nsubcarrier\'s profile data.\n\nRead TxBf profile PN\t:\niwpriv ra0 set TxBfProfilePnRead      =xx (PFMU ID)\n\nWrite TxBf profile PN :\niwpriv ra0 set TxBfProfilePnWrite     =Profile ID:B..." /* TRUNCATED STRING LITERAL */
          );
  }
  return 1;
}

