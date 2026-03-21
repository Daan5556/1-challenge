# IP Addressing

**Author:** Daan Eggen  
**Date:** 19/03/2026  
**Version:** 1.0

---

The network will consist of various edge gateways. The gateways will host a
private network, where edge devices can connect to. In this document I will
describe how these networks will look like. I will go over IP assignment,
addressing and subnetting.

| Abbreviation | Meaning                             |
| ------------ | ----------------------------------- |
| DHCP         | Dynamic Host Configuration Protocol |
| DNS          | Domain Name System                  |

## Addressing

The gateways will use `DHCP` to assign their network settings. This way, the
edge devices can be flexible, because the they are "naive", independent of
environment. This also ensures efficient IP assignment and avoids conflicts.

For the DHCP server, `dnsmasq`[^dnsmasq] will be used. Its light weight and
battle tested. It not only provides DHCP capabilities, but DNS as well. DNS can
potentially be used to route traffic via a reverse proxy for load balancing.

## Subnet

The networks will have a maximum of 10 edge devices. To have the network operate
as efficient as possible, a right subnet mask should be picked.

A subnet mask of `/28` gives 14 usable IPs, which is sufficient. It allows the
network to slightly grow if needed.

## Address ranges

For the network IP, I decided to follow the recommendation given in RFC
1918[^rfc1918]. For small, private networks they recommend using `192.68.0.1`.

So, if we apply the subnet mask, we will get the following network:

**Network:** `192.168.0.0/28`  
**Usable range:** `192.168.0.1 – 192.168.0.14`  
**Broadcast address:** `192.168.1.15`

[^dnsmasq]: https://thekelleys.org.uk/dnsmasq/doc.html

[^rfc1918]: https://datatracker.ietf.org/doc/html/rfc1918
