#!/bin/sh

read -p "-----MT7915 5G ATED TX Test---BEGIN----Press Enter To Continue!"
read -p "Please confirm the packet capture channel: 1(bgn)!! Press Enter To Continue!"
echo "11B  11M  CH1   抓取信道：1(bgn)"
`iwpriv wlan0 set ATE=TXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan0 set ATEIPG=50`
`iwpriv wlan0 set ATETXMODE=0`
`iwpriv wlan0 set ATETXMCS=3`
`iwpriv wlan0 set ATETXBW=0`
`iwpriv wlan0 set ATETXGI=0`
`iwpriv wlan0 set ATETXLDPC=1`
`iwpriv wlan0 set ATETXLEN=1024`
`iwpriv wlan0 set ATETXANT=1`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXCNT=2000`
`iwpriv wlan0 set ATECHANNEL=1`
`iwpriv wlan0 set ATETXPOW0=36`
`iwpriv wlan0 set ATE=TXCOMMIT`
`iwpriv wlan0 set ATE=TXFRAME`


echo "11g  54M  CH1   抓取信道：1(bgn)"
`iwpriv wlan0 set ATE=TXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan0 set ATEIPG=50`
`iwpriv wlan0 set ATETXMODE=1`
`iwpriv wlan0 set ATETXMCS=7`
`iwpriv wlan0 set ATETXBW=0`
`iwpriv wlan0 set ATETXGI=0`
`iwpriv wlan0 set ATETXLDPC=1`
`iwpriv wlan0 set ATETXLEN=1024`
`iwpriv wlan0 set ATETXANT=1`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXCNT=2000`
`iwpriv wlan0 set ATECHANNEL=1`
`iwpriv wlan0 set ATETXPOW0=36`
`iwpriv wlan0 set ATE=TXCOMMIT`
`iwpriv wlan0 set ATE=TXFRAME`

echo "11n MCS7 65M  抓取信道：1(bgn)"
`iwpriv wlan0 set ATE=TXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan0 set ATEIPG=50`
`iwpriv wlan0 set ATETXMODE=2`
`iwpriv wlan0 set ATETXMCS=7`
`iwpriv wlan0 set ATETXBW=0`
`iwpriv wlan0 set ATETXGI=0`
`iwpriv wlan0 set ATETXLDPC=1`
`iwpriv wlan0 set ATETXLEN=1024`
`iwpriv wlan0 set ATETXANT=1`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXCNT=2000`
`iwpriv wlan0 set ATECHANNEL=1`
`iwpriv wlan0 set ATE=TXCOMMIT`
`iwpriv wlan0 set ATE=TXFRAME`

read -p "Please confirm the packet capture channel: 6(bgn)!! Press Enter To Continue!"
echo "11b  11M  CH6   抓取信道：6(bgn)"
`iwpriv wlan0 set ATE=TXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan0 set ATEIPG=50`
`iwpriv wlan0 set ATETXMODE=0`
`iwpriv wlan0 set ATETXMCS=3`
`iwpriv wlan0 set ATETXBW=0`
`iwpriv wlan0 set ATETXGI=0`
`iwpriv wlan0 set ATETXLDPC=1`
`iwpriv wlan0 set ATETXLEN=1024`
`iwpriv wlan0 set ATETXANT=1`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXCNT=2000`
`iwpriv wlan0 set ATECHANNEL=6`
`iwpriv wlan0 set ATETXPOW0=36`
`iwpriv wlan0 set ATE=TXCOMMIT`
`iwpriv wlan0 set ATE=TXFRAME`

echo "11g  54M  CH1   抓取信道：6(bgn)"
`iwpriv wlan0 set ATE=TXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan0 set ATEIPG=50`
`iwpriv wlan0 set ATETXMODE=1`
`iwpriv wlan0 set ATETXMCS=7`
`iwpriv wlan0 set ATETXBW=0`
`iwpriv wlan0 set ATETXGI=0`
`iwpriv wlan0 set ATETXLDPC=1`
`iwpriv wlan0 set ATETXLEN=1024`
`iwpriv wlan0 set ATETXANT=1`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXCNT=2000`
`iwpriv wlan0 set ATECHANNEL=6`
`iwpriv wlan0 set ATE=TXCOMMIT`
`iwpriv wlan0 set ATE=TXFRAME`


echo "11n MCS7 65M  抓取信道：6(bgn)"
`iwpriv wlan0 set ATE=TXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan0 set ATEIPG=50`
`iwpriv wlan0 set ATETXMODE=2`
`iwpriv wlan0 set ATETXMCS=7`
`iwpriv wlan0 set ATETXBW=0`
`iwpriv wlan0 set ATETXGI=0`
`iwpriv wlan0 set ATETXLDPC=1`
`iwpriv wlan0 set ATETXLEN=1024`
`iwpriv wlan0 set ATETXANT=1`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXCNT=2000`
`iwpriv wlan0 set ATECHANNEL=6`
`iwpriv wlan0 set ATE=TXCOMMIT`
`iwpriv wlan0 set ATE=TXFRAME`


read -p "Please confirm the packet capture channel: 11(bgn)!! Press Enter To Continue!"
echo "11b  11M  CH6   抓取信道：11(bgn)"
`iwpriv wlan0 set ATE=TXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan0 set ATEIPG=50`
`iwpriv wlan0 set ATETXMODE=0`
`iwpriv wlan0 set ATETXMCS=3`
`iwpriv wlan0 set ATETXBW=0`
`iwpriv wlan0 set ATETXGI=0`
`iwpriv wlan0 set ATETXLDPC=1`
`iwpriv wlan0 set ATETXLEN=1024`
`iwpriv wlan0 set ATETXANT=1`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXCNT=2000`
`iwpriv wlan0 set ATECHANNEL=11`
`iwpriv wlan0 set ATETXPOW0=36`
`iwpriv wlan0 set ATE=TXCOMMIT`
`iwpriv wlan0 set ATE=TXFRAME`

echo "11g  54M  CH1   抓取信道：11(bgn)"
`iwpriv wlan0 set ATE=TXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan0 set ATEIPG=50`
`iwpriv wlan0 set ATETXMODE=1`
`iwpriv wlan0 set ATETXMCS=7`
`iwpriv wlan0 set ATETXBW=0`
`iwpriv wlan0 set ATETXGI=0`
`iwpriv wlan0 set ATETXLDPC=1`
`iwpriv wlan0 set ATETXLEN=1024`
`iwpriv wlan0 set ATETXANT=1`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXCNT=2000`
`iwpriv wlan0 set ATECHANNEL=11`
`iwpriv wlan0 set ATE=TXCOMMIT`
`iwpriv wlan0 set ATE=TXFRAME`


echo "11n MCS7 65M  抓取信道：11(bgn)"
`iwpriv wlan0 set ATE=TXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan0 set ATEIPG=50`
`iwpriv wlan0 set ATETXMODE=2`
`iwpriv wlan0 set ATETXMCS=7`
`iwpriv wlan0 set ATETXBW=0`
`iwpriv wlan0 set ATETXGI=0`
`iwpriv wlan0 set ATETXLDPC=1`
`iwpriv wlan0 set ATETXLEN=1024`
`iwpriv wlan0 set ATETXANT=1`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXCNT=2000`
`iwpriv wlan0 set ATECHANNEL=11`
`iwpriv wlan0 set ATE=TXCOMMIT`
`iwpriv wlan0 set ATE=TXFRAME`



read -p "Please confirm the packet capture channel: 1(n40h)!! Press Enter To Continue!"
echo "11n MCS7 135M  抓取信道：1(n40h)"
`iwpriv wlan0 set ATE=TXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan0 set ATEIPG=50`
`iwpriv wlan0 set ATETXMODE=2`
`iwpriv wlan0 set ATETXMCS=7`
`iwpriv wlan0 set ATETXBW=1:1`
`iwpriv wlan0 set ATETXGI=0`
`iwpriv wlan0 set ATETXLDPC=1`
`iwpriv wlan0 set ATETXLEN=1024`
`iwpriv wlan0 set ATETXANT=0`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXCNT=2000`
`iwpriv wlan0 set ATECHANNEL=3`
`iwpriv wlan0 set ATE=TXCOMMIT`
`iwpriv wlan0 set ATE=TXFRAME`




read -p "Please confirm the packet capture channel: 4(n40h)!! Press Enter To Continue!"
echo "11n MCS7 135M  抓取信道：4(n40h)"
`iwpriv wlan0 set ATE=TXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan0 set ATEIPG=50`
`iwpriv wlan0 set ATETXMODE=2`
`iwpriv wlan0 set ATETXMCS=7`
`iwpriv wlan0 set ATETXBW=1:1`
`iwpriv wlan0 set ATETXGI=0`
`iwpriv wlan0 set ATETXLDPC=1`
`iwpriv wlan0 set ATETXLEN=1024`
`iwpriv wlan0 set ATETXANT=0`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXCNT=2000`
`iwpriv wlan0 set ATECHANNEL=6`
`iwpriv wlan0 set ATE=TXCOMMIT`
`iwpriv wlan0 set ATE=TXFRAME`



read -p "Please confirm the packet capture channel: 7(n40h)!! Press Enter To Continue!"
echo "11n MCS7 135M  抓取信道：7(n40h)"
`iwpriv wlan0 set ATE=TXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan0 set ATEIPG=50`
`iwpriv wlan0 set ATETXMODE=2`
`iwpriv wlan0 set ATETXMCS=7`
`iwpriv wlan0 set ATETXBW=1:1`
`iwpriv wlan0 set ATETXGI=0`
`iwpriv wlan0 set ATETXLDPC=1`
`iwpriv wlan0 set ATETXLEN=1024`
`iwpriv wlan0 set ATETXANT=0`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXCNT=2000`
`iwpriv wlan0 set ATECHANNEL=9`
`iwpriv wlan0 set ATE=TXCOMMIT`
`iwpriv wlan0 set ATE=TXFRAME`



read -p "Please confirm the packet capture channel: 1(80MHz)!! Press Enter To Continue!"
echo "11ax MCS11 286.8M  抓取信道：1(80MHz)"
`iwpriv wlan0 set ATE=TXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan0 set ATEIPG=50`
`iwpriv wlan0 set ATETXMODE=8`
`iwpriv wlan0 set ATETXMCS=11`
`iwpriv wlan0 set ATETXBW=1:1`
`iwpriv wlan0 set ATETXGI=0`
`iwpriv wlan0 set ATETXLDPC=1`
`iwpriv wlan0 set ATETXLEN=1024`
`iwpriv wlan0 set ATETXANT=1`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXCNT=2000`
`iwpriv wlan0 set ATECHANNEL=3`
`iwpriv wlan0 set ATE=TXCOMMIT`
`iwpriv wlan0 set ATE=TXFRAME`


read -p "Please confirm the packet capture channel: 4(80MHz)!! Press Enter To Continue!"
echo "11ax MCS11 286.8M  抓取信道：4(80MHz)"
`iwpriv wlan0 set ATE=TXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan0 set ATEIPG=50`
`iwpriv wlan0 set ATETXMODE=8`
`iwpriv wlan0 set ATETXMCS=11`
`iwpriv wlan0 set ATETXBW=1:1`
`iwpriv wlan0 set ATETXGI=0`
`iwpriv wlan0 set ATETXLDPC=1`
`iwpriv wlan0 set ATETXLEN=1024`
`iwpriv wlan0 set ATETXANT=1`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXCNT=2000`
`iwpriv wlan0 set ATECHANNEL=6`
`iwpriv wlan0 set ATE=TXCOMMIT`
`iwpriv wlan0 set ATE=TXFRAME`


read -p "Please confirm the packet capture channel: 7(80MHz)!! Press Enter To Continue!"
echo "11ax MCS11 286.8M  抓取信道：7(80MHz)"
`iwpriv wlan0 set ATE=TXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan0 set ATEIPG=50`
`iwpriv wlan0 set ATETXMODE=8`
`iwpriv wlan0 set ATETXMCS=11`
`iwpriv wlan0 set ATETXBW=1:1`
`iwpriv wlan0 set ATETXGI=0`
`iwpriv wlan0 set ATETXLDPC=1`
`iwpriv wlan0 set ATETXLEN=1024`
`iwpriv wlan0 set ATETXANT=1`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXCNT=2000`
`iwpriv wlan0 set ATECHANNEL=9`
`iwpriv wlan0 set ATE=TXCOMMIT`
`iwpriv wlan0 set ATE=TXFRAME`



read -p "-----MT7915 5G ATED RX Test---BEGIN----Press Enter To Continue!"
read -p "Please confirm the packet capture channel: 1(bgn)!! Press Enter To Continue!"
echo "11B  11M  CH1   抓取信道：1(bgn)"
`iwpriv wlan0 set ATE=RXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ResetCounter=0`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATERXSTATRESET=0`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXBW=0`
`iwpriv wlan0 set ATECHANNEL=1:1`
`iwpriv wlan0 set ATETXMODE=0`
`iwpriv wlan0 set ATETXMCS=3`
`iwpriv wlan0 set ATE=RXFRAME`
ping -i 1 -c 2 127.0.0.1 > /var/tmp/null
`iwpriv wlan0 set ATERXFER=1`
`iwpriv wlan0 set ATERXSTAT=1`


echo "11g  54M  CH1   抓取信道：1(bgn)"
`iwpriv wlan0 set ATE=RXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ResetCounter=0`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATERXSTATRESET=0`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXBW=0`
`iwpriv wlan0 set ATECHANNEL=1:1`
`iwpriv wlan0 set ATETXMODE=1`
`iwpriv wlan0 set ATETXMCS=7`
`iwpriv wlan0 set ATE=RXFRAME`
ping -i 1 -c 2 127.0.0.1 > /var/tmp/null
`iwpriv wlan0 set ATERXFER=1`
`iwpriv wlan0 set ATERXSTAT=1`

echo "11n MCS7 65M  抓取信道：1(bgn)"
`iwpriv wlan0 set ATE=RXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ResetCounter=0`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATERXSTATRESET=0`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXBW=0`
`iwpriv wlan0 set ATECHANNEL=1:1`
`iwpriv wlan0 set ATETXMODE=2`
`iwpriv wlan0 set ATETXMCS=7`
`iwpriv wlan0 set ATE=RXFRAME`
ping -i 1 -c 2 127.0.0.1 > /var/tmp/null
`iwpriv wlan0 set ATERXFER=1`
`iwpriv wlan0 set ATERXSTAT=1`

read -p "Please confirm the packet capture channel: 6(bgn)!! Press Enter To Continue!"
echo "11b  11M  CH6   抓取信道：6(bgn)"
`iwpriv wlan0 set ATE=RXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ResetCounter=0`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATERXSTATRESET=0`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXBW=0`
`iwpriv wlan0 set ATECHANNEL=6:1`
`iwpriv wlan0 set ATETXMODE=0`
`iwpriv wlan0 set ATETXMCS=3`
`iwpriv wlan0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan0 set ATERXFER=1`
`iwpriv wlan0 set ATERXSTAT=1`

echo "11g  54M  CH1   抓取信道：6(bgn)"
`iwpriv wlan0 set ATE=RXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ResetCounter=0`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATERXSTATRESET=0`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXBW=0`
`iwpriv wlan0 set ATECHANNEL=6:1`
`iwpriv wlan0 set ATETXMODE=1`
`iwpriv wlan0 set ATETXMCS=7`
`iwpriv wlan0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan0 set ATERXFER=1`
`iwpriv wlan0 set ATERXSTAT=1`


echo "11n MCS7 65M  抓取信道：6(bgn)"
`iwpriv wlan0 set ATE=RXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ResetCounter=0`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATERXSTATRESET=0`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXBW=0`
`iwpriv wlan0 set ATECHANNEL=6:1`
`iwpriv wlan0 set ATETXMODE=2`
`iwpriv wlan0 set ATETXMCS=7`
`iwpriv wlan0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan0 set ATERXFER=1`
`iwpriv wlan0 set ATERXSTAT=1`


read -p "Please confirm the packet capture channel: 11(bgn)!! Press Enter To Continue!"
echo "11b  11M  CH6   抓取信道：11(bgn)"
`iwpriv wlan0 set ATE=RXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ResetCounter=0`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATERXSTATRESET=0`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXBW=0`
`iwpriv wlan0 set ATECHANNEL=11:1`
`iwpriv wlan0 set ATETXMODE=0`
`iwpriv wlan0 set ATETXMCS=3`
`iwpriv wlan0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan0 set ATERXFER=1`
`iwpriv wlan0 set ATERXSTAT=1`

echo "11g  54M  CH1   抓取信道：11(bgn)"
`iwpriv wlan0 set ATE=RXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ResetCounter=0`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATERXSTATRESET=0`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXBW=0`
`iwpriv wlan0 set ATECHANNEL=11:1`
`iwpriv wlan0 set ATETXMODE=1`
`iwpriv wlan0 set ATETXMCS=7`
`iwpriv wlan0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan0 set ATERXFER=1`
`iwpriv wlan0 set ATERXSTAT=1`


echo "11n MCS7 65M  抓取信道：11(bgn)"
`iwpriv wlan0 set ATE=RXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ResetCounter=0`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATERXSTATRESET=0`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXBW=0`
`iwpriv wlan0 set ATECHANNEL=11:1`
`iwpriv wlan0 set ATETXMODE=2`
`iwpriv wlan0 set ATETXMCS=7`
`iwpriv wlan0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan0 set ATERXFER=1`
`iwpriv wlan0 set ATERXSTAT=1`


read -p "Please confirm the packet capture channel: 1(n40h)!! Press Enter To Continue!"
echo "11n MCS7 135M  抓取信道：1(n40h)"
`iwpriv wlan0 set ATE=RXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ResetCounter=0`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATERXSTATRESET=0`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXBW=1`
`iwpriv wlan0 set ATECHANNEL=3:1`
`iwpriv wlan0 set ATETXMODE=2`
`iwpriv wlan0 set ATETXMCS=7`
`iwpriv wlan0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan0 set ATERXFER=1`
`iwpriv wlan0 set ATERXSTAT=1`




read -p "Please confirm the packet capture channel: 4(n40h)!! Press Enter To Continue!"
echo "11n MCS7 135M  抓取信道：4(n40h)"
`iwpriv wlan0 set ATE=RXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ResetCounter=0`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATERXSTATRESET=0`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXBW=1`
`iwpriv wlan0 set ATECHANNEL=6:1`
`iwpriv wlan0 set ATETXMODE=2`
`iwpriv wlan0 set ATETXMCS=7`
`iwpriv wlan0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan0 set ATERXFER=1`
`iwpriv wlan0 set ATERXSTAT=1`


read -p "Please confirm the packet capture channel: 7(n40h)!! Press Enter To Continue!"
echo "11n MCS7 135M  抓取信道：7(n40h)"
`iwpriv wlan0 set ATE=RXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ResetCounter=0`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATERXSTATRESET=0`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXBW=1`
`iwpriv wlan0 set ATECHANNEL=9:1`
`iwpriv wlan0 set ATETXMODE=2`
`iwpriv wlan0 set ATETXMCS=7`
`iwpriv wlan0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan0 set ATERXFER=1`
`iwpriv wlan0 set ATERXSTAT=1`



read -p "Please confirm the packet capture channel: 1(80MHz)!! Press Enter To Continue!"
echo "11ax MCS11 286.8M  抓取信道：1(80MHz)"
`iwpriv wlan0 set ATE=RXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ResetCounter=0`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATERXSTATRESET=0`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXBW=1`
`iwpriv wlan0 set ATECHANNEL=3:1`
`iwpriv wlan0 set ATETXMODE=8`
`iwpriv wlan0 set ATETXMCS=11`
`iwpriv wlan0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan0 set ATERXFER=1`
`iwpriv wlan0 set ATERXSTAT=1`


read -p "Please confirm the packet capture channel: 4(80MHz)!! Press Enter To Continue!"
echo "11ax MCS11 286.8M  抓取信道：4(80MHz)"
`iwpriv wlan0 set ATE=RXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ResetCounter=0`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATERXSTATRESET=0`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXBW=1`
`iwpriv wlan0 set ATECHANNEL=6:1`
`iwpriv wlan0 set ATETXMODE=8`
`iwpriv wlan0 set ATETXMCS=11`
`iwpriv wlan0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan0 set ATERXFER=1`
`iwpriv wlan0 set ATERXSTAT=1`


read -p "Please confirm the packet capture channel: 7(80MHz)!! Press Enter To Continue!"
echo "11ax MCS11 286.8M  抓取信道：7(80MHz)"
`iwpriv wlan0 set ATE=RXSTOP`
`iwpriv wlan0 set ATE=ATESTART`
`iwpriv wlan0 set ResetCounter=0`
`iwpriv wlan0 set ATECTRLBANDIDX=0`
`iwpriv wlan0 set ATERXSTATRESET=0`
`iwpriv wlan0 set ATERXANT=1`
`iwpriv wlan0 set ATETXBW=1`
`iwpriv wlan0 set ATECHANNEL=9:1`
`iwpriv wlan0 set ATETXMODE=8`
`iwpriv wlan0 set ATETXMCS=11`
`iwpriv wlan0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan0 set ATERXFER=1`
`iwpriv wlan0 set ATERXSTAT=1`

`iwpriv wlan0 set ATE=RXSTOP`
# 退出ATE模式
`iwpriv wlan0 set ATE=ATESTOP`

