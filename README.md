Connection Handler
==================

**Warning!!! This code is for educational use only. It shows various code smells 
and design issues in order to train students in seeing issues. Please see the
result after the review as well at the branch 
[review_2013_04_16](https://github.com/cdonat/connection_handler_teaching/tree/review_2013_04_16).
additional branches will be added in future**


Problem Description
-------------------

Write a component that does the following things:

1. Establish a TCP connection
2. Do some handshaking on that connection (see "Handshaking" below)
3. Write messages to that connection (see "Message Framing" below)
4. Read messages from the connection (see "Message Framing" below)
5. Do additional handshaking for shitting doen the connection and (see "Handshaking" below)
6. Close the connection


### Message Framing

Messages are written to the TCP Stream with a two byte length field at the 
beginning. The length is given in bytes, the byte order of that field is
network byte order. The length field value does not include the length field 
itsself.

### Handshaking

All handshaking is done with messages according to the section "Message 
Framing". When the Test states that someone 'sends "abc"', that means, that a
message with the length of 3 and the content "abc" is written to the TCP
connection.

#### Login

A session beginns with the client sending "helo" in a message with exaclty 
these four characters. The server answers with the same four bytes. 

Now the client tries to log in to the server sending its credentials. These
are encoded as "user:" followed by the username, a zero byte followed by 
"passwd:" and the password. An example for such a message would be 
"user:test\0passwd:123qwe" for a user called "test" with a password "123qwe".

When the credentials provided to the server are accepted it answers with 
"ACK" else it anwers with "NOACK" or closes the connection. When the 
connection is not closed, the client can retry the login on the same 
connection.

After the login was successfull, the client tells the server that it has 
understood by sending "ACKACK".


#### Logout

To cleanly close the connection, the client first sends a Message containing 
"bye". The server answers with "bye". Then the connection can be closed.

