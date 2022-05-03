# SNMP-COM CONCEPT

Predicted implementation of the following SNMP features in client-server architecture 

## SNMP Client and Server
- MIB Implementation on server

root-iso(1)-org(3)-dod(6)-internet(1)-mgmt(2)-mib(1):

.1.3.6.1.2.1

| branch |variables with id |
| ------------- | ------------- |
| system(1)  | osName(1), hostName(2), kernelVersion(3), osVersion(4), hardware(5)  |
| interfaces(2)  | ifName(1) -> ipVersion(1) -> ipAddress(2)  |
| at(3)  | interface(1) -> macAddress  |
| ip(4) | destination(1) -> gateway(1) -> iface(2) -> metric(3) -> mtu(4) netstat -s will be used  |
| icmp(5)  | netstat -s will be used   |
| tcp(6)  | netstat -s will be used    |
| udp(7)  | netstat -s will be used    |
| egp(8)  | Content Cell  |
| transmission(10)  | Content Cell  |

![inna](https://user-images.githubusercontent.com/56030577/166424522-db5e60f6-1ef5-40c3-978c-745663f95e55.gif)

## SNMP OPERATIONS
- GET
- GETNEXT
- GETBULK

![projekt](https://user-images.githubusercontent.com/56030577/164969774-87e56a36-9491-43ef-af19-d6fdd58b1258.png)
