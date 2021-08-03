## Tracker
A personal project to quckly document time and task to a file.

### Install: unix based
To install you need:
* git
* make
* glibc

```
git clone "https://github.com/elicatza/tracker"
cd tracker
make
mkdir ~/var
```

### Use
The default name of binary is called tracker, which is located at /usr/local/bin/tracker.  
The binary will get the system date, time and timezone on execution. 
It will write this information to it's default location ~/var/tracker/tracker.  

##### Flags
When a flag is inclueded with the command like:
```
tracker -s
```

The program with find a pre-written message for that spesific flag which is by default "sleep".
After a valid message is found it will make a file with an equal name at ~/var/tracker/.
The date along with the message will now be written to the file.  

<br>

If multiple flags are entered it will edit or make a file for each valid flag.  


### Settings
