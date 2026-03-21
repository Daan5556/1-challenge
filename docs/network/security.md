# Security

**Author:** Daan Eggen  
**Date:** 21/03/2026  
**Version:** 1.0

---

The gateway network will be accessible via a WPA2 protected access point. I need
to harden this setup, in case the network is compromised.

If an attackers gets access to the network, they can read/write messages in all
the topics. They can mimic legitimate devices and send fake messages. This is a
risk for the data integrity.

They can also flood the access point with data and execute a Denial of Service
(DoS) attack.

The following measurements are taken to mitigate these risks.

## Authentication

The MQTT broker should implement basic authentication This will protect the
broker even if an attacker compromises the network. To do this, I will manage a
password file on the edge gateway. This file will contain username and hashed
password pairs for every edge device. Like so:

```plaintext
ED-1001-01:$7$101...
```

This way, every edge device has to authenticate on connection, limiting access.

## Firewall rules

I know exactly what network communicating is going to be required beforehand. I
know that the TCP protocol is going to be used over port 1883.

I will use `iptables` to **exclusively** allow this traffic, and SSH traffic for
management.

```plaintext
-A INPUT -p tcp --dport 1883 -j ACCEPT
```

If the network is compromised, the attacker cannot access any other
(unprotected) network services.

## TLS

If an attacker is on the network, they can inspect traffic, exposing potential
sensitive data. They can also employ a "man in the middle" attack by
impersonating the broker.

TLS tackles both of these risks. The broker will present a signed certificate to
the clients, proving identity. The traffic will also be encrypted, mitigating
the risk that its read by the attacker.

I will use a self signed certificate and add it to the `mosquitto`
configuration.

```conf
cafile /path/to/ca.crt
certfile /path/to/server.crt
keyfile /path/to/server.key
```
