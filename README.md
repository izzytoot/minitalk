# 💬 Minitalk

## 1. About the project
The purpose of this project is to code a small data exchange program between server and client using UNIX signals.

For more information check the subject: [**subject of minitalk**](https://github.com/izzytoot/minitalk/blob/main/en.subject.pdf).


## 2. Usage

### 2.1 Compiling

To compile, go to the project folder and run:

```shell
$ make
```
### Testing

To test the program launch the "server" and the "client" in different terminals with the following:

```shell
$ ./server
```

This will show your PID, later used by the client, and will keep open while waiting to receive a message from the client. Then run:

```shell
$ ./client "PID" "message string"
```

The "message string" should then appear on the server window.
