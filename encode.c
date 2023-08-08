#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "types.h"
#include "common.h"

/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    printf("height = %u\n", height);

    // Return image capacity
    return width * height * 3;
}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

    	return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

    	return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

    	return e_failure;
    }

    // No failure return e_success
    return e_success;
}
Status do_encoding(EncodeInfo *encInfo)                                                                                                                                       {                                                                                                                                                                                     if(open_files(encInfo)==e_success)                                                                                                                                            {                                                                                                                                                                                     printf("Opened files succesfully.\n");                                                                                                                                }                                                                                                                                                                             else                                                                                                                                                                          {                                                                                                                                                                                     printf("Error : Unable to open files.\n");                                                                                                                                    return e_failure;                                                                                                                                                     }                                                                                                                                                                             if(check_capacity(encInfo)==e_success)                                                                                                                                        {                                                                                                                                                                                     printf("Check capacity success.\n");                                                                                                                                  }                                                                                                                                                                             else                                                                                                                                                                          {                                                                                                                                                                                     printf("Error : Check capacity failed.\n");                                                                                                                                   return e_failure;                                                                                                                                                     }                                                                                                                                                                             rewind(encInfo->fptr_src_image);                                                                                                                                              if(copy_bmp_header(encInfo->fptr_src_image, encInfo->fptr_stego_image)==e_success)                                                                                            {                                                                                                                                                                                     printf("Copying header data succesful.\n");                                                                                                                           }                                                                                                                                                                             else                                                                                                                                                                          {                                                                                                                                                                                     printf("Error : Copying header data failed.\n");                                                                                                                      }                                                                                                                                                            
	if(encode_magic_string(MAGIC_STRING,encInfo)==e_success)
	{
		printf("Magic string encoded succesfully.\n");
	}
	else
	{
		printf("Error : Magic string encoding failed.\n");
	}
	if(encode_secret_file_extn_size(strlen(encInfo->extn_secret_file),encInfo)==e_success)
		{
			printf("encoding secret file extension size success.\n");
		}
	else
	{
		printf("Error : Secret file extension size encoding failed.\n");
		return e_failure;
	}
	if(encode_secret_file_extn(encInfo->extn_secret_file,encInfo)==e_success)
	{
		printf("Secret file extension encoded.\n");
	}	
	else
	{
		printf("Error : Encoding secret file extension failed'\n");
		return e_failure;
	}
	if(encode_secret_file_size(encInfo->size_secret_file,encInfo)==e_success)
	{
		printf("Encoding secret file size success.\n");
	}
	else
	{
		printf("Error : Encoding secret file size failed.\n");
	}
	if(encode_secret_file_data(encInfo)==e_success)
	{
		printf("Encoding secret file data success.\n");
	}
	else
	{
		printf("Error : Encoding secret file data failed");
	}
	if(copy_remaining_img_data(encInfo->fptr_src_image, encInfo->fptr_stego_image)==e_success)
	{
		printf("Copied remaining data.\n");
	}
	else
	{
		printf("Error : Unable to copy remaining data.\n");
	}
	return e_success;
}
	Status check_capacity(EncodeInfo *encInfo)                                                                                                                                    {                                                                                                                                                                                     encInfo->image_capacity = get_image_size_for_bmp(encInfo->fptr_src_image);                                                                                                    fseek(encInfo->fptr_secret,0,SEEK_END);                                                                                                                                       encInfo->size_secret_file = ftell(encInfo->fptr_secret);                                                                                                                      if(encInfo->image_capacity > strlen(MAGIC_STRING)+4+strlen(encInfo->extn_secret_file)+4+encInfo->size_secret_file)                                                            {                                                                                                                                                                                     return e_success;                                                                                                                                                     }                                                                                                                                                                             else                                                                                                                                                                          {                                                                                                                                                                                     return e_failure;                                                                                                                                                     }                                                                                                                                                                     }    
Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
	char str[54];
	fread(str,sizeof(char),54,fptr_src_image);
	fwrite(str,sizeof(char),54,fptr_dest_image);
	return e_success;
}
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
	encode_data_to_image(magic_string,strlen(MAGIC_STRING), encInfo->fptr_src_image, encInfo->fptr_stego_image);
	return e_success;
}
Status encode_data_to_image(char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image)
{
	char str[8];
	for(int i=0;i<size;i++)
	{
		fread(str,sizeof(char),8,fptr_src_image);
		encode_byte_to_lsb(data[i],str);
	        fwrite(str,sizeof(char),8,fptr_stego_image);
	}
}
Status encode_byte_to_lsb(char data, char *image_buffer)
{
	for(int i=7;i>=0;i--)
	{
		image_buffer[7-i]=((data&(1<<i))>>i)|(image_buffer[7-i]&0xFE);
	}
}
Status encode_secret_file_extn_size(int size , EncodeInfo *encInfo)
{
	char str[32];
	fread(str,sizeof(int),8,encInfo->fptr_src_image);
	encode_size_to_lsb(size,str);
	fwrite(str,sizeof(int),8,encInfo->fptr_stego_image);
	return e_success;
}
Status encode_size_to_lsb(int data,char *str )
{
	for(int i=31;i>=0;i--)
	{
		str[31-i]=((data&(1<<i))>>i)|(str[31-i]&0xFE);
	}
}
Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo)
{
	encode_data_to_image(file_extn,strlen(encInfo->extn_secret_file),encInfo->fptr_src_image,encInfo->fptr_stego_image);
	return e_success;
}
Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
{
	encode_secret_file_extn_size(file_size , encInfo);
	return e_success;
}

Status encode_secret_file_data(EncodeInfo *encInfo)
{
	rewind(encInfo->fptr_secret);
	char str[encInfo->size_secret_file];
	fread(str,sizeof(char),encInfo->size_secret_file,encInfo->fptr_secret);
	encode_data_to_image(str,encInfo->size_secret_file,encInfo->fptr_src_image,encInfo->fptr_stego_image);
	return e_success;
}
Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
	char ch[1];
	while(fread(ch,1,1,fptr_src)>0)
	{
		fwrite(ch,1,1,fptr_dest);
	}
	return e_success;
}
