# steganography
Steganography is a technique of hiding secret data inside a normal file.
The secret data is arranged in the normal file such that every bit of secret file memory is arranged at the lsb of nomal file byte.
It helps to transfer the confidential data .
the a.out file is the executable file which takes the inputs as follows(Command Line Arguments).
./a.out -e [normal file] [secret data file] [output file]  --> For encoding
./a.out -d [encoded file] [output file]  --> For decoding
The extension of secret file stored durung encoding,so the output file at decoding will be automatically converts into the original extension file.
In this project, I used .bmp as the normal file which stores the secret data and the secret file of any type.
The data is copied such that the image data of normal bmp file will be same as the encoded bmp file.
A magic string (#*) is allocated to the encoded file ,so it will be easy to find the encoded file.
