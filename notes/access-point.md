# Access Point

So I created a virtual router using `hostapd`. It uses the following
configuration:

```conf
interface=wlan0
driver=nl80211
ssid=test-ap
hw_mode=g
channel=6
wmm_enabled=0
auth_algs=1
wpa=2
wpa_passphrase=12345678
wpa_key_mgmt=WPA-PSK
rsn_pairwise=CCMP
```

Next, I gave the interface an IP address:

```bash
sudo ip addr add 192.168.4.1/24 dev wlan0
```

You can flush the IP address with:

```bash
 sudo ip addr flush  wlan0
```
