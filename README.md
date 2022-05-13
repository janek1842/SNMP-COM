# SNMP-COM CONCEPT
Very simple client-server app for observing basic SNMP operations (GET, GET NEXT, GET BULK) 
 


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
- GETNEXT
- GETBULK

## Simple DEMO :)

Client
- GET OID 
![image](https://user-images.githubusercontent.com/56030577/168314790-c19b7c63-9675-4b0d-93a6-511abe1361f9.png)

- GET NEXT
![image](https://user-images.githubusercontent.com/56030577/168314960-1fd95aec-261d-481b-8ff9-6382ccafd232.png)

- GET BULK
![image](https://user-images.githubusercontent.com/56030577/168315165-a4737bf5-fcf2-410e-8870-de33840e368b.png)

Server
![image](https://user-images.githubusercontent.com/56030577/168315271-ebc95f0c-c507-4f7c-b952-2ca374f4dddc.png)




