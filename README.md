# Image Steganography using LSB Encoding and Decoding

Steganography is a technique of hiding secret data inside a normal file.

The objective was to send a secret text file encoded inside an image of bmp file format.

Encoded the length of the secret text and then encoded the data into the LSB of the image bytes. 

The decoding process involves decoding the length and then decoding the text bit by bit. 

The final output is the secret text after decoding.

# Process

The secret data is arranged in the normal file such that every bit of secret file memory is arranged at the lsb of nomal file byte.

It helps to transfer the confidential data .

the a.out file is the executable file which takes the inputs as follows(Command Line Arguments).

./a.out -e [normal file] [secret data file] [output file]  --> For encoding.

./a.out -d [encoded file] [output file]  --> For decoding.

The extension of secret file stored durung encoding,so the output file at decoding will be automatically converts into the original extension file.

In this project, I used .bmp as the normal file which stores the secret data and the secret file of any type.

The data is copied such that the image data of normal bmp file will be same as the encoded bmp file.

A magic string (#*) is allocated to the encoded file ,so it will be easy to find the encoded file.

# Used softwares :

![image](https://github.com/dhanudj000/steganography/assets/122971572/b362a876-368a-4161-b3e5-5a3fb1c23531)
![image](https://github.com/dhanudj000/steganography/assets/122971572/d2d39aff-a196-476d-bf81-dc8962373902)

# Learnings & Challenges :

->Understanding of pixels and header of image file by doing literature study.

->Transforming the embedded information to the destination without changing properties of original image.

->Faced challenges while doing bitwise manipulation of data to embed as well to retrieve the data from the destination image which was solved by self-understanding.
