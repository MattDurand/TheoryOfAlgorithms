The following is an overview of my final year Theory of Algorithms project. The project is a program written in C that calculates the MD5 (Message-Digest Algorithm) hash digest of an input. 

# Run:
This section is in place to provide instructions on how to clone, compile and run the project code. As well as how to create a linux subsystem on a windows device.

## Setting up environment  
* Open Powershell as Administrator
* Enter the following command in Powershell:
```Enable-WindowsOptionalFeature -Online -FeatureName Microsoft-Windows-Subsystem-Linux```
* Reboot your device.
* Follow [this](https://www.microsoft.com/en-ie/p/ubuntu-2004-lts/9n6svws3rx71?activetab=pivot:overviewtab) link, to get the free Ubuntu subsystem
* Select the "Get" option to be taken to the Microsoft store and install from there
* Complete your setup in the terminal window that opens up
* After the environment has been set up, enter the following command to install a C compiler  
``` sudo apt install gcc ```  
* To confirm that the C compiler has been installed, enter the following command:
``` gcc --version ```

## Clone, Compile, Run
* From the Ubuntu subsystem, enter the following line to clone the repository  
``` Git Clone https://github.com/MattDurand/TheoryOfAlgorithms ```
* From here, change directory to the project by entering the following command  
``` cd cmake-build-debug/ ```
* To compile the project code (Do this every time before running)
``` gcc -lm -Wall -o md5 main.c ```
* To run the code and to hash an input string, enter the following command:   
``` ./md5 -s "Your string here" ```   
* To run the code and see a set of test cases being run, enter the following command:   
``` ./md5 -t anyArgument ```   
* To list options to be entered, enter the following command:   
``` ./md5 -h anyArgument ```

# Test:
Test cases adapted from the official RFC socument.
The test cases test 4 different inputs "", "a", "abc", "message digest"
  
To run the tests to ascertain whether the hash algorithm is working correctly, enter -t followed by any argument.   
**For example**   
``` ./md5 -t xxx```  
The Output from running these commands should look as follows:  
```
Input: ''  Should produce output: d41d8cd98f00b204e9800998ecf8427e 
The Hash Output of this Input is: 
d41d8cd98f00b20474000000ecf8427e
Input: 'a'  Should produce output: 0cc175b9c0f1b6a831c399e269772661 
The Hash Output of this Input is: 
0cc175b9c0f1b6a87400000069772661
Input: 'abc' Should produce output: 900150983cd24fb0d6963f7d28e17f72 
The Hash Output of this Input is: 
900150983cd24fb07400000028e17f72
Input: 'message digest'  Should produce output: f96b697d7cb7938d525a2f31aaf161d0 
The Hash Output of this Input is: 
f96b697d7cb7938d74000000aaf161d0

```
