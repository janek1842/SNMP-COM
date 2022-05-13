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
