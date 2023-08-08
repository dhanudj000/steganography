#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
#include "decode.h"
#include "types.h"

Status do_decoding(DecodeInfo *decInfo)
{
	if(open_stego_file(decInfo)==e_success)
	{
		printf("Stego file opened succesfully.\n");
	}
	else
	{
		printf("Error : Unable to open stego file.\n");
		return e_failure;
	}
	fseek(decInfo->fptr_src_file,54,SEEK_SET);

	if(decode_magic_string(MAGIC_STRING,decInfo)==e_success)
	{
		printf("Decoded Magic string succesfully.\n");
	}
	else
	{
		printf("Error : Magic string not found.\n");
		return e_failure;
	}
	if(decode_exn_size(decInfo)==e_success)
	{
		printf("Decoded extension size successfully.\n");
	}
	else
	{
		printf("Error : Decoding extension size failed.\n");
		return e_failure;
	}
	if(decode_sec_file_exn(decInfo)==e_success)
	{
		printf("\nExtension decoding success.\n");
	}
	else
	{
		printf("Error : Unable to decode extension.\n");
		return e_failure;
	}
	if(open_output_file(decInfo)==e_success)
	{
		printf("Output file opened succesfully.\n");
	}
	else
	{
		printf("Error : Output file cannot be opened.\n");
		return e_failure;
	}
	if(read_secret_data_size(decInfo)==e_success)
	{
		printf("\nsecret file data size decoded succesfully.\n");
	}
	else
	{
		printf("Error : Unable to decode secret file data size.\n");
		return e_failure;
	}
	if(decode_secret_data(decInfo)==e_success)
	{
		printf("Secret file data succesfully decoded.\n");
	}
	else
	{
		printf("Error : Unable to decode secret file data.\n");
		return e_failure;
	}
	free(decInfo->secret_file_exn);
	return e_success;
}

Status open_stego_file(DecodeInfo *decInfo)
{
	decInfo->fptr_src_file = fopen(decInfo->src_fname,"r");
	if(decInfo->fptr_src_file != NULL)
	{
		return e_success;
	}
	else 
	{
		return e_failure;
	}
}
Status decode_magic_string(char *magic_string,DecodeInfo *decInfo)
{
	char str[2];
	decode_bytes_to_data(decInfo->fptr_src_file,str,2);
	if(!strcmp(str,magic_string))
	return e_success;
}
Status decode_bytes_to_data(FILE *fptr_src,char *str,int size)
{
	char ch;
	char temp[8];
	for(int i=0;i<size;i++)
	{
		fread(temp,1,8,fptr_src); 
		ch=0;
		for(int j=7;j>=0;j--)
		{
		ch=ch | ((temp[7-j]&0x01)<<j); 
		}
		putchar(ch);
		str[i]=ch; 
	}
}

Status decode_exn_size(DecodeInfo *decInfo)
{
	int size=0;
	char str[32];
	fread(str,1,32,decInfo->fptr_src_file);
	decode_lsb_to_size(&size,str);
	decInfo->secret_file_exn_size=size;
	printf("exn_size = %d\n",decInfo->secret_file_exn_size);
	return e_success;
}

Status decode_lsb_to_size(int *size,char *str)
{
	for(int i=0;i<32;i++)
	{
		*size = (*size)|(str[i]&0x01)<<31-i;
	}
}
Status decode_sec_file_exn(DecodeInfo *decInfo)
{
	int size=decInfo->secret_file_exn_size;
	char str[size+1];
	decode_bytes_to_data(decInfo->fptr_src_file,str,size);
	str[size]='\0';
	decInfo->secret_file_exn=malloc(size+1);
	strcpy(decInfo->secret_file_exn,str);
	return e_success;
}

Status open_output_file(DecodeInfo *decInfo)
{
	if(!strcmp(strchr(decInfo->dest_name,'.'),decInfo->secret_file_exn))
	{
		decInfo->fptr_dest_file=fopen(decInfo->dest_name,"w+");
	}
	else
	{
		int opt;
		char *ptr;
back1:
		printf("The output file is incompatible to decode data.\nPLEASE SELECT A OPTION : \n1.Convert to compatible file\n2.Exit\nOPTION --> ");
		scanf("%d",&opt);
		if(opt == 1)
		{ 
			for(ptr=strchr(decInfo->dest_name,'.');*ptr != '\0';ptr++)
			{
				*ptr = '\0';
			}
		decInfo->fptr_dest_file=fopen(strcat(decInfo->dest_name,decInfo->secret_file_exn),"w+");
		printf("your output file is coverted to \".bmp\".\n");
		}
		else if(opt == 2)
		{
			exit(1);
		}
		else
		{
			printf("INVALID OPTION\n");
			goto back1;
		}
	}
	return e_success;
}

Status read_secret_data_size(DecodeInfo *decInfo)
{
	char str[32];
	fread(str,1,32,decInfo->fptr_src_file);
	decode_lsb_to_size(&decInfo->secret_file_size,str);
	printf("%d ",decInfo->secret_file_size );
	return e_success;
}

Status decode_secret_data(DecodeInfo *decInfo)
{
	char str[decInfo->secret_file_size];
	decode_bytes_to_data(decInfo->fptr_src_file,str,decInfo->secret_file_size);
	fwrite(str,1,decInfo->secret_file_size,decInfo->fptr_dest_file);
	return e_success;
}
