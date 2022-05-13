# SNMP-COM
Very simple client-server app for observing basic SNMP operations (GET, GET NEXT, GET BULK) 

## How to run ? 
- Clone the repository
  - git clone https://github.com/janek1842/SNMP-COM.git
  - Code was tested positively on Ubuntu 

- Server
```
cd SNMP-COM
cd server
sudo gcc daytimeudpsrvv6.c
sudo ./a.out
```
- Client
```
cd SNMP-COM
cd client
sudo gcc daytimeudpcliv6.c
sudo ./a.out <server ipv6 address>
```

## SNMP Client and Server
Predicted implementation of the following SNMP features in client-server architecture
- MIB Implementation on server
- Client operations for getting server MIB informations 
- Server operations for returning informations

root-iso(1)-org(3)-dod(6)-internet(1)-mgmt(2)-mib(1):

**DEFAULT OID:** .1.3.6.1.2.1.1.1

| branch |variables with id / related bash commands to parse|
| ------------- | ------------- |
| system(1)  | osName(1), hostName(2), kernelVersion(3), osVersion(4), hardware(5)  |

## IMPLEMENTED SNMP OPERATIONS
- GET OID
- SET OID
- GET
- GET NEXT
- GET BULK

## Simple DEMO :)
### Client
- GET OID 
<img src="https://user-images.githubusercontent.com/56030577/168314790-c19b7c63-9675-4b0d-93a6-511abe1361f9.png" width="700" height="800" align="center"> 


- GET NEXT
<img src="https://user-images.githubusercontent.com/56030577/168314960-1fd95aec-261d-481b-8ff9-6382ccafd232.png" width="700" height="800" align="center">

- GET BULK
<img src="https://user-images.githubusercontent.com/56030577/168315165-a4737bf5-fcf2-410e-8870-de33840e368b.png" width="700" height="800" align="center">

### Server

<img src="https://user-images.githubusercontent.com/56030577/168315271-ebc95f0c-c507-4f7c-b952-2ca374f4dddc.png" width="700" height="800" align="center">




