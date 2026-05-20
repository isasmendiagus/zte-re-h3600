#!/bin/sh
read -p "-----MT7915 5G ATED TX Test---BEGIN----Press Enter To Continue!"
read -p "Please confirm the packet capture channel: 36(an)!! Press Enter To Continue!"
echo "11a 6m CH36   抓取信道：36(an)"
`iwpriv wlan5g0 set ATE=TXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan5g0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATEIPG=50`
`iwpriv wlan5g0 set ATETXMODE=1`
`iwpriv wlan5g0 set ATETXMCS=0`
`iwpriv wlan5g0 set ATETXBW=0`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATETXLDPC=1`
`iwpriv wlan5g0 set ATETXLEN=1024`
`iwpriv wlan5g0 set ATETXANT=1`
`iwpriv wlan5g0 set ATETXCNT=2000`
`iwpriv wlan5g0 set ATECHANNEL=36:1`
`iwpriv wlan5g0 set ATE=TXCOMMIT`
`iwpriv wlan5g0 set ATE=TXFRAME`

echo "5G 11n 6.5M   抓取信道：36(an)"
`iwpriv wlan5g0 set ATE=TXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan5g0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATEIPG=50`
`iwpriv wlan5g0 set ATETXMODE=2`
`iwpriv wlan5g0 set ATETXMCS=0`
`iwpriv wlan5g0 set ATETXBW=0`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATETXLDPC=1`
`iwpriv wlan5g0 set ATETXLEN=1024`
`iwpriv wlan5g0 set ATETXANT=1`
`iwpriv wlan5g0 set ATETXCNT=2000`
`iwpriv wlan5g0 set ATECHANNEL=36:1`
`iwpriv wlan5g0 set ATE=TXCOMMIT`
`iwpriv wlan5g0 set ATE=TXFRAME`

echo "5G 11n 65M   抓取信道：36(an)"
`iwpriv wlan5g0 set ATE=TXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan5g0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATEIPG=50`
`iwpriv wlan5g0 set ATETXMODE=2`
`iwpriv wlan5g0 set ATETXMCS=7`
`iwpriv wlan5g0 set ATETXBW=0`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATETXLDPC=1`
`iwpriv wlan5g0 set ATETXLEN=1024`
`iwpriv wlan5g0 set ATETXANT=1`
`iwpriv wlan5g0 set ATETXCNT=2000`
`iwpriv wlan5g0 set ATECHANNEL=36:1`
`iwpriv wlan5g0 set ATE=TXCOMMIT`
`iwpriv wlan5g0 set ATE=TXFRAME`



read -p "Please confirm the packet capture channel: 64(an)!! Press Enter To Continue!"
echo "11a 6m CH36   抓取信道：64(an)"
`iwpriv wlan5g0 set ATE=TXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan5g0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATEIPG=50`
`iwpriv wlan5g0 set ATETXMODE=1`
`iwpriv wlan5g0 set ATETXMCS=0`
`iwpriv wlan5g0 set ATETXBW=0`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATETXLDPC=1`
`iwpriv wlan5g0 set ATETXLEN=1024`
`iwpriv wlan5g0 set ATETXANT=1`
`iwpriv wlan5g0 set ATETXCNT=2000`
`iwpriv wlan5g0 set ATECHANNEL=64:1`
`iwpriv wlan5g0 set ATE=TXCOMMIT`
`iwpriv wlan5g0 set ATE=TXFRAME`

echo "5G 11n 6.5M   抓取信道：64(an)"
`iwpriv wlan5g0 set ATE=TXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan5g0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATEIPG=50`
`iwpriv wlan5g0 set ATETXMODE=2`
`iwpriv wlan5g0 set ATETXMCS=0`
`iwpriv wlan5g0 set ATETXBW=0`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATETXLDPC=1`
`iwpriv wlan5g0 set ATETXLEN=1024`
`iwpriv wlan5g0 set ATETXANT=1`
`iwpriv wlan5g0 set ATETXCNT=2000`
`iwpriv wlan5g0 set ATECHANNEL=64:1`
`iwpriv wlan5g0 set ATE=TXCOMMIT`
`iwpriv wlan5g0 set ATE=TXFRAME`


echo "5G 11n 65M   抓取信道：64(an)"
`iwpriv wlan5g0 set ATE=TXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan5g0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATEIPG=50`
`iwpriv wlan5g0 set ATETXMODE=2`
`iwpriv wlan5g0 set ATETXMCS=7`
`iwpriv wlan5g0 set ATETXBW=0`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATETXLDPC=1`
`iwpriv wlan5g0 set ATETXLEN=1024`
`iwpriv wlan5g0 set ATETXANT=1`
`iwpriv wlan5g0 set ATETXCNT=2000`
`iwpriv wlan5g0 set ATECHANNEL=64:1`
`iwpriv wlan5g0 set ATE=TXCOMMIT`
`iwpriv wlan5g0 set ATE=TXFRAME`


read -p "Please confirm the packet capture channel: 100(an)!! Press Enter To Continue!"
echo "11a 6m CH36   抓取信道：100(an)"
`iwpriv wlan5g0 set ATE=TXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan5g0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATEIPG=50`
`iwpriv wlan5g0 set ATETXMODE=1`
`iwpriv wlan5g0 set ATETXMCS=0`
`iwpriv wlan5g0 set ATETXBW=0`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATETXLDPC=1`
`iwpriv wlan5g0 set ATETXLEN=1024`
`iwpriv wlan5g0 set ATETXANT=1`
`iwpriv wlan5g0 set ATETXCNT=2000`
`iwpriv wlan5g0 set ATECHANNEL=100:1`
`iwpriv wlan5g0 set ATE=TXCOMMIT`
`iwpriv wlan5g0 set ATE=TXFRAME`


echo "5G 11n 6.5M   抓取信道：100(an)"
`iwpriv wlan5g0 set ATE=TXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan5g0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATEIPG=50`
`iwpriv wlan5g0 set ATETXMODE=2`
`iwpriv wlan5g0 set ATETXMCS=0`
`iwpriv wlan5g0 set ATETXBW=0`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATETXLDPC=1`
`iwpriv wlan5g0 set ATETXLEN=1024`
`iwpriv wlan5g0 set ATETXANT=1`
`iwpriv wlan5g0 set ATETXCNT=2000`
`iwpriv wlan5g0 set ATECHANNEL=100:1`
`iwpriv wlan5g0 set ATE=TXCOMMIT`
`iwpriv wlan5g0 set ATE=TXFRAME`

echo "5G 11n 65M   抓取信道：100(an)"
`iwpriv wlan5g0 set ATE=TXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan5g0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATEIPG=50`
`iwpriv wlan5g0 set ATETXMODE=2`
`iwpriv wlan5g0 set ATETXMCS=7`
`iwpriv wlan5g0 set ATETXBW=0`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATETXLDPC=1`
`iwpriv wlan5g0 set ATETXLEN=1024`
`iwpriv wlan5g0 set ATETXANT=1`
`iwpriv wlan5g0 set ATETXCNT=2000`
`iwpriv wlan5g0 set ATECHANNEL=100:1`
`iwpriv wlan5g0 set ATE=TXCOMMIT`
`iwpriv wlan5g0 set ATE=TXFRAME`

read -p "Please confirm the packet capture channel: 149(an)!! Press Enter To Continue!"
echo "11a 6m CH36   抓取信道：149(an)"
`iwpriv wlan5g0 set ATE=TXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan5g0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATEIPG=50`
`iwpriv wlan5g0 set ATETXMODE=1`
`iwpriv wlan5g0 set ATETXMCS=0`
`iwpriv wlan5g0 set ATETXBW=0`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATETXLDPC=1`
`iwpriv wlan5g0 set ATETXLEN=1024`
`iwpriv wlan5g0 set ATETXANT=1`
`iwpriv wlan5g0 set ATETXCNT=2000`
`iwpriv wlan5g0 set ATECHANNEL=149:1`
`iwpriv wlan5g0 set ATE=TXCOMMIT`
`iwpriv wlan5g0 set ATE=TXFRAME`

echo "5G 11n 6.5M   抓取信道：149(an)"
`iwpriv wlan5g0 set ATE=TXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan5g0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATEIPG=50`
`iwpriv wlan5g0 set ATETXMODE=2`
`iwpriv wlan5g0 set ATETXMCS=0`
`iwpriv wlan5g0 set ATETXBW=0`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATETXLDPC=1`
`iwpriv wlan5g0 set ATETXLEN=1024`
`iwpriv wlan5g0 set ATETXANT=1`
`iwpriv wlan5g0 set ATETXCNT=2000`
`iwpriv wlan5g0 set ATECHANNEL=149:1`
`iwpriv wlan5g0 set ATE=TXCOMMIT`
`iwpriv wlan5g0 set ATE=TXFRAME`

echo "5G 11n 65M   抓取信道：149(an)"
`iwpriv wlan5g0 set ATE=TXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan5g0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATEIPG=50`
`iwpriv wlan5g0 set ATETXMODE=2`
`iwpriv wlan5g0 set ATETXMCS=7`
`iwpriv wlan5g0 set ATETXBW=0`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATETXLDPC=1`
`iwpriv wlan5g0 set ATETXLEN=1024`
`iwpriv wlan5g0 set ATETXANT=1`
`iwpriv wlan5g0 set ATETXCNT=2000`
`iwpriv wlan5g0 set ATECHANNEL=149:1`
`iwpriv wlan5g0 set ATE=TXCOMMIT`
`iwpriv wlan5g0 set ATE=TXFRAME`







read -p "Please confirm the packet capture channel: 36(n40h)!! Press Enter To Continue!"
echo "5G 11n 135M   抓取信道：36(n40h)"
`iwpriv wlan5g0 set ATE=TXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan5g0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATEIPG=50`
`iwpriv wlan5g0 set ATETXMODE=2`
`iwpriv wlan5g0 set ATETXMCS=7`
`iwpriv wlan5g0 set ATETXBW=1`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATETXLDPC=1`
`iwpriv wlan5g0 set ATETXLEN=1024`
`iwpriv wlan5g0 set ATETXANT=1`
`iwpriv wlan5g0 set ATETXCNT=500`
`iwpriv wlan5g0 set ATECHANNEL=38:1`
`iwpriv wlan5g0 set ATE=TXCOMMIT`
`iwpriv wlan5g0 set ATE=TXFRAME`



read -p "Please confirm the packet capture channel: 60(n40h)!! Press Enter To Continue!"
echo "5G 11n 135M   抓取信道：60(n40h)"
`iwpriv wlan5g0 set ATE=TXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan5g0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATEIPG=50`
`iwpriv wlan5g0 set ATETXMODE=2`
`iwpriv wlan5g0 set ATETXMCS=7`
`iwpriv wlan5g0 set ATETXBW=1`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATETXLDPC=1`
`iwpriv wlan5g0 set ATETXLEN=1024`
`iwpriv wlan5g0 set ATETXANT=1`
`iwpriv wlan5g0 set ATETXCNT=500`
`iwpriv wlan5g0 set ATECHANNEL=62:1`
`iwpriv wlan5g0 set ATE=TXCOMMIT`
`iwpriv wlan5g0 set ATE=TXFRAME`



read -p "Please confirm the packet capture channel: 100(n40h)!! Press Enter To Continue!"
echo "5G 11n 135M   抓取信道：100(n40h)"
`iwpriv wlan5g0 set ATE=TXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan5g0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATEIPG=50`
`iwpriv wlan5g0 set ATETXMODE=2`
`iwpriv wlan5g0 set ATETXMCS=7`
`iwpriv wlan5g0 set ATETXBW=1`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATETXLDPC=1`
`iwpriv wlan5g0 set ATETXLEN=1024`
`iwpriv wlan5g0 set ATETXANT=1`
`iwpriv wlan5g0 set ATETXCNT=500`
`iwpriv wlan5g0 set ATECHANNEL=102:1`
`iwpriv wlan5g0 set ATE=TXCOMMIT`
`iwpriv wlan5g0 set ATE=TXFRAME`


read -p "Please confirm the packet capture channel: 149(n40h)!! Press Enter To Continue!"
echo "5G 11n 135M   抓取信道：149(n40h)"
`iwpriv wlan5g0 set ATE=TXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan5g0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATEIPG=50`
`iwpriv wlan5g0 set ATETXMODE=2`
`iwpriv wlan5g0 set ATETXMCS=7`
`iwpriv wlan5g0 set ATETXBW=1`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATETXLDPC=1`
`iwpriv wlan5g0 set ATETXLEN=1024`
`iwpriv wlan5g0 set ATETXANT=1`
`iwpriv wlan5g0 set ATETXCNT=500`
`iwpriv wlan5g0 set ATECHANNEL=151:1`
`iwpriv wlan5g0 set ATE=TXCOMMIT`
`iwpriv wlan5g0 set ATE=TXFRAME`



read -p "Please confirm the packet capture channel: 36(ac)!! Press Enter To Continue!"
echo "5G 11ac 390M   抓取信道：36(ac)"
`iwpriv wlan5g0 set ATE=TXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan5g0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATEIPG=50`
`iwpriv wlan5g0 set ATETXMODE=4`
`iwpriv wlan5g0 set ATETXMCS=9`
`iwpriv wlan5g0 set ATETXBW=2`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATETXLDPC=1`
`iwpriv wlan5g0 set ATETXLEN=1024`
`iwpriv wlan5g0 set ATETXANT=1`
`iwpriv wlan5g0 set ATETXCNT=2000`
`iwpriv wlan5g0 set ATECHANNEL=42:1`
`iwpriv wlan5g0 set ATE=TXCOMMIT`
`iwpriv wlan5g0 set ATE=TXFRAME`





read -p "Please confirm the packet capture channel: 64(ac)!! Press Enter To Continue!"
echo "5G 11ac 390M   抓取信道：64(ac)"
`iwpriv wlan5g0 set ATE=TXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan5g0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATEIPG=50`
`iwpriv wlan5g0 set ATETXMODE=4`
`iwpriv wlan5g0 set ATETXMCS=9`
`iwpriv wlan5g0 set ATETXBW=2`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATETXLDPC=1`
`iwpriv wlan5g0 set ATETXLEN=1024`
`iwpriv wlan5g0 set ATETXANT=1`
`iwpriv wlan5g0 set ATETXCNT=2000`
`iwpriv wlan5g0 set ATECHANNEL=58:1`
`iwpriv wlan5g0 set ATE=TXCOMMIT`
`iwpriv wlan5g0 set ATE=TXFRAME`



read -p "Please confirm the packet capture channel: 100(ac)!! Press Enter To Continue!"
echo "5G  11ac 390M   抓取信道：100(ac)"
`iwpriv wlan5g0 set ATE=TXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan5g0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATEIPG=50`
`iwpriv wlan5g0 set ATETXMODE=4`
`iwpriv wlan5g0 set ATETXMCS=9`
`iwpriv wlan5g0 set ATETXBW=2`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATETXLDPC=1`
`iwpriv wlan5g0 set ATETXLEN=1024`
`iwpriv wlan5g0 set ATETXANT=1`
`iwpriv wlan5g0 set ATETXCNT=2000`
`iwpriv wlan5g0 set ATECHANNEL=106:1`
`iwpriv wlan5g0 set ATE=TXCOMMIT`
`iwpriv wlan5g0 set ATE=TXFRAME`



read -p "Please confirm the packet capture channel: 149(ac)!! Press Enter To Continue!"
echo "5G 11ac 390M   抓取信道：149(ac)"
`iwpriv wlan5g0 set ATE=TXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan5g0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATEIPG=50`
`iwpriv wlan5g0 set ATETXMODE=4`
`iwpriv wlan5g0 set ATETXMCS=9`
`iwpriv wlan5g0 set ATETXBW=2`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATETXLDPC=1`
`iwpriv wlan5g0 set ATETXLEN=1024`
`iwpriv wlan5g0 set ATETXANT=1`
`iwpriv wlan5g0 set ATETXCNT=2000`
`iwpriv wlan5g0 set ATECHANNEL=155:1`
`iwpriv wlan5g0 set ATE=TXCOMMIT`
`iwpriv wlan5g0 set ATE=TXFRAME`





read -p "Please confirm the packet capture channel: 36(80MHz)!! Press Enter To Continue!"
echo "5G 11ax 600M   抓取信道：36(80MHz)"
`iwpriv wlan5g0 set ATE=TXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan5g0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATEIPG=50`
`iwpriv wlan5g0 set ATETXMODE=8`
`iwpriv wlan5g0 set ATETXMCS=11`
`iwpriv wlan5g0 set ATETXBW=2:2`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATETXLDPC=1`
`iwpriv wlan5g0 set ATETXLEN=1024`
`iwpriv wlan5g0 set ATETXANT=4`
`iwpriv wlan5g0 set ATERXANT=4`
`iwpriv wlan5g0 set ATETXCNT=20000`
`iwpriv wlan5g0 set ATECHANNEL=42:1`
`iwpriv wlan5g0 set ATE=TXCOMMIT`
`iwpriv wlan5g0 set ATE=TXFRAME`


read -p "Please confirm the packet capture channel: 64(80MHz)!! Press Enter To Continue!"
echo "5G 11ax 600M   抓取信道：64(80MHz)"
`iwpriv wlan5g0 set ATE=TXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan5g0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATEIPG=50`
`iwpriv wlan5g0 set ATETXMODE=8`
`iwpriv wlan5g0 set ATETXMCS=11`
`iwpriv wlan5g0 set ATETXBW=2:2`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATETXLDPC=1`
`iwpriv wlan5g0 set ATETXLEN=1024`
`iwpriv wlan5g0 set ATETXANT=4`
`iwpriv wlan5g0 set ATERXANT=4`
`iwpriv wlan5g0 set ATETXCNT=20000`
`iwpriv wlan5g0 set ATECHANNEL=58:1`
`iwpriv wlan5g0 set ATE=TXCOMMIT`
`iwpriv wlan5g0 set ATE=TXFRAME`


read -p "Please confirm the packet capture channel: 100(80MHz)!! Press Enter To Continue!"
echo "5G 11ax 600M   抓取信道：100(80MHz)"
`iwpriv wlan5g0 set ATE=TXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan5g0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATEIPG=50`
`iwpriv wlan5g0 set ATETXMODE=8`
`iwpriv wlan5g0 set ATETXMCS=11`
`iwpriv wlan5g0 set ATETXBW=2:2`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATETXLDPC=1`
`iwpriv wlan5g0 set ATETXLEN=1024`
`iwpriv wlan5g0 set ATETXANT=4`
`iwpriv wlan5g0 set ATERXANT=4`
`iwpriv wlan5g0 set ATETXCNT=20000`
`iwpriv wlan5g0 set ATECHANNEL=106:1`
`iwpriv wlan5g0 set ATE=TXCOMMIT`
`iwpriv wlan5g0 set ATE=TXFRAME`


read -p "Please confirm the packet capture channel: 149(80MHz)!! Press Enter To Continue!"
echo "5G 11ax 600M   抓取信道：149(80MHz)"
`iwpriv wlan5g0 set ATE=TXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATEDA=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATESA=00:aa:bb:cc:dd:ee`
`iwpriv wlan5g0 set ATEBSSID=00:11:22:33:44:55`
`iwpriv wlan5g0 set ATEIPG=50`
`iwpriv wlan5g0 set ATETXMODE=8`
`iwpriv wlan5g0 set ATETXMCS=11`
`iwpriv wlan5g0 set ATETXBW=2:2`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATETXLDPC=1`
`iwpriv wlan5g0 set ATETXLEN=1024`
`iwpriv wlan5g0 set ATETXANT=4`
`iwpriv wlan5g0 set ATERXANT=4`
`iwpriv wlan5g0 set ATETXCNT=20000`
`iwpriv wlan5g0 set ATECHANNEL=155:1`
`iwpriv wlan5g0 set ATE=TXCOMMIT`
`iwpriv wlan5g0 set ATE=TXFRAME`



read -p "-----MT7915 5G ATED RX Test---BEGIN----Press Enter To Continue!"
read -p "Please confirm the packet capture channel: 36(an)!! Press Enter To Continue!"
echo "11a 6m CH36   抓取信道：36(an)"
`iwpriv wlan5g0 set ATE=RXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ResetCounter=0`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATERXSTATRESET=1`
`iwpriv wlan5g0 set ATETXBW=0`
`iwpriv wlan5g0 set ATETXANT=4`
`iwpriv wlan5g0 set ATERXANT=1`
`iwpriv wlan5g0 set ATETXMODE=1`
`iwpriv wlan5g0 set ATETXMCS=0`
`iwpriv wlan5g0 set ATECHANNEL=36:1`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATE=RXFRAME`
ping -i 1 -c 2 127.0.0.1 > /var/tmp/null
`iwpriv wlan5g0 set ATERXFER=1`
`iwpriv wlan5g0 set ATERXSTAT=1`

echo "5G 11n 6.5M   抓取信道：36(an)"
`iwpriv wlan5g0 set ATE=RXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ResetCounter=0`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATERXSTATRESET=1`
`iwpriv wlan5g0 set ATETXBW=0`
`iwpriv wlan5g0 set ATETXANT=4`
`iwpriv wlan5g0 set ATERXANT=1`
`iwpriv wlan5g0 set ATETXMODE=2`
`iwpriv wlan5g0 set ATETXMCS=0`
`iwpriv wlan5g0 set ATECHANNEL=36:1`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATE=RXFRAME`
ping -i 1 -c 2 127.0.0.1 > /var/tmp/null
`iwpriv wlan5g0 set ATERXFER=1`
`iwpriv wlan5g0 set ATERXSTAT=1`

echo "5G 11n 65M   抓取信道：36(an)"
`iwpriv wlan5g0 set ATE=RXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ResetCounter=0`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATERXSTATRESET=1`
`iwpriv wlan5g0 set ATETXBW=0`
`iwpriv wlan5g0 set ATETXANT=4`
`iwpriv wlan5g0 set ATERXANT=1`
`iwpriv wlan5g0 set ATETXMODE=2`
`iwpriv wlan5g0 set ATETXMCS=7`
`iwpriv wlan5g0 set ATECHANNEL=36:1`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATE=RXFRAME`
ping -i 1 -c 2 127.0.0.1 > /var/tmp/null
`iwpriv wlan5g0 set ATERXFER=1`
`iwpriv wlan5g0 set ATERXSTAT=1`



read -p "Please confirm the packet capture channel: 64(an)!! Press Enter To Continue!"
echo "11a 6m CH36   抓取信道：64(an)"
`iwpriv wlan5g0 set ATE=RXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ResetCounter=0`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATERXSTATRESET=1`
`iwpriv wlan5g0 set ATETXBW=0`
`iwpriv wlan5g0 set ATETXANT=4`
`iwpriv wlan5g0 set ATERXANT=1`
`iwpriv wlan5g0 set ATETXMODE=1`
`iwpriv wlan5g0 set ATETXMCS=0`
`iwpriv wlan5g0 set ATECHANNEL=64:1`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan5g0 set ATERXFER=1`
`iwpriv wlan5g0 set ATERXSTAT=1`

echo "5G 11n 6.5M   抓取信道：64(an)"
`iwpriv wlan5g0 set ATE=RXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ResetCounter=0`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATERXSTATRESET=1`
`iwpriv wlan5g0 set ATETXBW=0`
`iwpriv wlan5g0 set ATETXANT=4`
`iwpriv wlan5g0 set ATERXANT=1`
`iwpriv wlan5g0 set ATETXMODE=2`
`iwpriv wlan5g0 set ATETXMCS=0`
`iwpriv wlan5g0 set ATECHANNEL=64:1`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan5g0 set ATERXFER=1`
`iwpriv wlan5g0 set ATERXSTAT=1`


echo "5G 11n 65M   抓取信道：64(an)"
`iwpriv wlan5g0 set ATE=RXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ResetCounter=0`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATERXSTATRESET=1`
`iwpriv wlan5g0 set ATETXBW=0`
`iwpriv wlan5g0 set ATETXANT=4`
`iwpriv wlan5g0 set ATERXANT=1`
`iwpriv wlan5g0 set ATETXMODE=2`
`iwpriv wlan5g0 set ATETXMCS=7`
`iwpriv wlan5g0 set ATECHANNEL=64:1`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan5g0 set ATERXFER=1`
`iwpriv wlan5g0 set ATERXSTAT=1`


read -p "Please confirm the packet capture channel: 100(an)!! Press Enter To Continue!"
echo "11a 6m CH36   抓取信道：100(an)"
`iwpriv wlan5g0 set ATE=RXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ResetCounter=0`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATERXSTATRESET=1`
`iwpriv wlan5g0 set ATETXBW=0`
`iwpriv wlan5g0 set ATETXANT=4`
`iwpriv wlan5g0 set ATERXANT=1`
`iwpriv wlan5g0 set ATETXMODE=1`
`iwpriv wlan5g0 set ATETXMCS=0`
`iwpriv wlan5g0 set ATECHANNEL=100:1`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan5g0 set ATERXFER=1`
`iwpriv wlan5g0 set ATERXSTAT=1`


echo "5G 11n 6.5M   抓取信道：100(an)"
`iwpriv wlan5g0 set ATE=RXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ResetCounter=0`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATERXSTATRESET=1`
`iwpriv wlan5g0 set ATETXBW=0`
`iwpriv wlan5g0 set ATETXANT=4`
`iwpriv wlan5g0 set ATERXANT=1`
`iwpriv wlan5g0 set ATETXMODE=2`
`iwpriv wlan5g0 set ATETXMCS=0`
`iwpriv wlan5g0 set ATECHANNEL=100:1`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan5g0 set ATERXFER=1`
`iwpriv wlan5g0 set ATERXSTAT=1`

echo "5G 11n 65M   抓取信道：100(an)"
`iwpriv wlan5g0 set ATE=RXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ResetCounter=0`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATERXSTATRESET=1`
`iwpriv wlan5g0 set ATETXBW=0`
`iwpriv wlan5g0 set ATETXANT=4`
`iwpriv wlan5g0 set ATERXANT=1`
`iwpriv wlan5g0 set ATETXMODE=2`
`iwpriv wlan5g0 set ATETXMCS=7`
`iwpriv wlan5g0 set ATECHANNEL=100:1`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan5g0 set ATERXFER=1`
`iwpriv wlan5g0 set ATERXSTAT=1`


read -p "Please confirm the packet capture channel: 149(an)!! Press Enter To Continue!"
echo "11a 6m CH36   抓取信道：149(an)"
`iwpriv wlan5g0 set ATE=RXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ResetCounter=0`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATERXSTATRESET=1`
`iwpriv wlan5g0 set ATETXBW=0`
`iwpriv wlan5g0 set ATETXANT=4`
`iwpriv wlan5g0 set ATERXANT=1`
`iwpriv wlan5g0 set ATETXMODE=1`
`iwpriv wlan5g0 set ATETXMCS=0`
`iwpriv wlan5g0 set ATECHANNEL=149:1`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan5g0 set ATERXFER=1`
`iwpriv wlan5g0 set ATERXSTAT=1`

echo "5G 11n 6.5M   抓取信道：149(an)"
`iwpriv wlan5g0 set ATE=RXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ResetCounter=0`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATERXSTATRESET=1`
`iwpriv wlan5g0 set ATETXBW=0`
`iwpriv wlan5g0 set ATETXANT=4`
`iwpriv wlan5g0 set ATERXANT=1`
`iwpriv wlan5g0 set ATETXMODE=2`
`iwpriv wlan5g0 set ATETXMCS=0`
`iwpriv wlan5g0 set ATECHANNEL=149:1`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan5g0 set ATERXFER=1`
`iwpriv wlan5g0 set ATERXSTAT=1`

echo "5G 11n 65M   抓取信道：149(an)"
`iwpriv wlan5g0 set ATE=RXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ResetCounter=0`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATERXSTATRESET=1`
`iwpriv wlan5g0 set ATETXBW=0`
`iwpriv wlan5g0 set ATETXANT=4`
`iwpriv wlan5g0 set ATERXANT=1`
`iwpriv wlan5g0 set ATETXMODE=2`
`iwpriv wlan5g0 set ATETXMCS=7`
`iwpriv wlan5g0 set ATECHANNEL=149:1`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan5g0 set ATERXFER=1`
`iwpriv wlan5g0 set ATERXSTAT=1`





read -p "Please confirm the packet capture channel: 36(n40h)!! Press Enter To Continue!"
echo "5G 11n 135M   抓取信道：36(n40h)"
`iwpriv wlan5g0 set ATE=RXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ResetCounter=0`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATERXSTATRESET=1`
`iwpriv wlan5g0 set ATETXBW=1`
`iwpriv wlan5g0 set ATETXANT=4`
`iwpriv wlan5g0 set ATERXANT=1`
`iwpriv wlan5g0 set ATETXMODE=2`
`iwpriv wlan5g0 set ATETXMCS=7`
`iwpriv wlan5g0 set ATECHANNEL=38:1`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan5g0 set ATERXFER=1`
`iwpriv wlan5g0 set ATERXSTAT=1`



read -p "Please confirm the packet capture channel: 60(n40h)!! Press Enter To Continue!"
echo "5G 11n 135M   抓取信道：60(n40h)"
`iwpriv wlan5g0 set ATE=RXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ResetCounter=0`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATERXSTATRESET=1`
`iwpriv wlan5g0 set ATETXBW=1`
`iwpriv wlan5g0 set ATETXANT=4`
`iwpriv wlan5g0 set ATERXANT=1`
`iwpriv wlan5g0 set ATETXMODE=2`
`iwpriv wlan5g0 set ATETXMCS=7`
`iwpriv wlan5g0 set ATECHANNEL=62:1`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan5g0 set ATERXFER=1`
`iwpriv wlan5g0 set ATERXSTAT=1`



read -p "Please confirm the packet capture channel: 100(n40h)!! Press Enter To Continue!"
echo "5G 11n 135M   抓取信道：100(n40h)"
`iwpriv wlan5g0 set ATE=RXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ResetCounter=0`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATERXSTATRESET=1`
`iwpriv wlan5g0 set ATETXBW=1`
`iwpriv wlan5g0 set ATETXANT=4`
`iwpriv wlan5g0 set ATERXANT=1`
`iwpriv wlan5g0 set ATETXMODE=2`
`iwpriv wlan5g0 set ATETXMCS=7`
`iwpriv wlan5g0 set ATECHANNEL=102:1`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan5g0 set ATERXFER=1`
`iwpriv wlan5g0 set ATERXSTAT=1`


read -p "Please confirm the packet capture channel: 149(n40h)!! Press Enter To Continue!"
echo "5G 11n 135M   抓取信道：149(n40h)"
`iwpriv wlan5g0 set ATE=RXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ResetCounter=0`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATERXSTATRESET=1`
`iwpriv wlan5g0 set ATETXBW=1`
`iwpriv wlan5g0 set ATETXANT=4`
`iwpriv wlan5g0 set ATERXANT=1`
`iwpriv wlan5g0 set ATETXMODE=2`
`iwpriv wlan5g0 set ATETXMCS=7`
`iwpriv wlan5g0 set ATECHANNEL=151:1`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan5g0 set ATERXFER=1`
`iwpriv wlan5g0 set ATERXSTAT=1`


read -p "Please confirm the packet capture channel: 36(ac)!! Press Enter To Continue!"
echo "5G 11ac 390M   抓取信道：36(ac)"
`iwpriv wlan5g0 set ATE=RXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ResetCounter=0`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATERXSTATRESET=1`
`iwpriv wlan5g0 set ATETXBW=2`
`iwpriv wlan5g0 set ATETXANT=4`
`iwpriv wlan5g0 set ATERXANT=1`
`iwpriv wlan5g0 set ATETXMODE=4`
`iwpriv wlan5g0 set ATETXMCS=9`
`iwpriv wlan5g0 set ATECHANNEL=42:1`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan5g0 set ATERXFER=1`
`iwpriv wlan5g0 set ATERXSTAT=1`



read -p "Please confirm the packet capture channel: 64(ac)!! Press Enter To Continue!"
echo "5G 11ac 390M   抓取信道：64(ac)"
`iwpriv wlan5g0 set ATE=RXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ResetCounter=0`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATERXSTATRESET=1`
`iwpriv wlan5g0 set ATETXBW=2`
`iwpriv wlan5g0 set ATETXANT=4`
`iwpriv wlan5g0 set ATERXANT=1`
`iwpriv wlan5g0 set ATETXMODE=4`
`iwpriv wlan5g0 set ATETXMCS=9`
`iwpriv wlan5g0 set ATECHANNEL=58:1`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan5g0 set ATERXFER=1`
`iwpriv wlan5g0 set ATERXSTAT=1`



read -p "Please confirm the packet capture channel: 100(ac)!! Press Enter To Continue!"
echo "5G  11ac 390M   抓取信道：100(ac)"
`iwpriv wlan5g0 set ATE=RXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ResetCounter=0`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATERXSTATRESET=1`
`iwpriv wlan5g0 set ATETXBW=2`
`iwpriv wlan5g0 set ATETXANT=4`
`iwpriv wlan5g0 set ATERXANT=1`
`iwpriv wlan5g0 set ATETXMODE=4`
`iwpriv wlan5g0 set ATETXMCS=9`
`iwpriv wlan5g0 set ATECHANNEL=106:1`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan5g0 set ATERXFER=1`
`iwpriv wlan5g0 set ATERXSTAT=1`



read -p "Please confirm the packet capture channel: 149(ac)!! Press Enter To Continue!"
echo "5G 11ac 390M   抓取信道：149(ac)"
`iwpriv wlan5g0 set ATE=RXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ResetCounter=0`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATERXSTATRESET=1`
`iwpriv wlan5g0 set ATETXBW=2`
`iwpriv wlan5g0 set ATETXANT=4`
`iwpriv wlan5g0 set ATERXANT=1`
`iwpriv wlan5g0 set ATETXMODE=4`
`iwpriv wlan5g0 set ATETXMCS=9`
`iwpriv wlan5g0 set ATECHANNEL=155:1`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan5g0 set ATERXFER=1`
`iwpriv wlan5g0 set ATERXSTAT=1`





read -p "Please confirm the packet capture channel: 36(80MHz)!! Press Enter To Continue!"
echo "5G 11ax 600M   抓取信道：36(80MHz)"
`iwpriv wlan5g0 set ATE=RXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ResetCounter=0`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATERXSTATRESET=1`
`iwpriv wlan5g0 set ATETXBW=2`
`iwpriv wlan5g0 set ATETXANT=4`
`iwpriv wlan5g0 set ATERXANT=1`
`iwpriv wlan5g0 set ATETXMODE=8`
`iwpriv wlan5g0 set ATETXMCS=11`
`iwpriv wlan5g0 set ATECHANNEL=42:1`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan5g0 set ATERXFER=1`
`iwpriv wlan5g0 set ATERXSTAT=1`


read -p "Please confirm the packet capture channel: 64(80MHz)!! Press Enter To Continue!"
echo "5G 11ax 600M   抓取信道：64(80MHz)"
`iwpriv wlan5g0 set ATE=RXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ResetCounter=0`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATERXSTATRESET=1`
`iwpriv wlan5g0 set ATETXBW=2`
`iwpriv wlan5g0 set ATETXANT=4`
`iwpriv wlan5g0 set ATERXANT=1`
`iwpriv wlan5g0 set ATETXMODE=8`
`iwpriv wlan5g0 set ATETXMCS=11`
`iwpriv wlan5g0 set ATECHANNEL=58:1`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan5g0 set ATERXFER=1`
`iwpriv wlan5g0 set ATERXSTAT=1`


read -p "Please confirm the packet capture channel: 100(80MHz)!! Press Enter To Continue!"
echo "5G 11ax 600M   抓取信道：100(80MHz)"
`iwpriv wlan5g0 set ATE=RXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ResetCounter=0`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATERXSTATRESET=1`
`iwpriv wlan5g0 set ATETXBW=2`
`iwpriv wlan5g0 set ATETXANT=4`
`iwpriv wlan5g0 set ATERXANT=1`
`iwpriv wlan5g0 set ATETXMODE=8`
`iwpriv wlan5g0 set ATETXMCS=11`
`iwpriv wlan5g0 set ATECHANNEL=106:1`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan5g0 set ATERXFER=1`
`iwpriv wlan5g0 set ATERXSTAT=1`


read -p "Please confirm the packet capture channel: 149(80MHz)!! Press Enter To Continue!"
echo "5G 11ax 600M   抓取信道：149(80MHz)"
`iwpriv wlan5g0 set ATE=RXSTOP`
`iwpriv wlan5g0 set ATE=ATESTART`
`iwpriv wlan5g0 set ResetCounter=0`
`iwpriv wlan5g0 set ATECTRLBANDIDX=1`
`iwpriv wlan5g0 set ATERXSTATRESET=1`
`iwpriv wlan5g0 set ATETXBW=2`
`iwpriv wlan5g0 set ATETXANT=4`
`iwpriv wlan5g0 set ATERXANT=1`
`iwpriv wlan5g0 set ATETXMODE=8`
`iwpriv wlan5g0 set ATETXMCS=11`
`iwpriv wlan5g0 set ATECHANNEL=155:1`
`iwpriv wlan5g0 set ATETXGI=0`
`iwpriv wlan5g0 set ATE=RXFRAME`
ping -i 1 -c 3 127.0.0.1 > /var/tmp/null
`iwpriv wlan5g0 set ATERXFER=1`
`iwpriv wlan5g0 set ATERXSTAT=1`

`iwpriv wlan5g0 set ATE=RXSTOP`
# 退出ATE模式
`iwpriv wlan5g0 set ATE=ATESTOP`
