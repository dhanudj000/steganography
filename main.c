#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "encode.h"
#include "decode.h"
#include "types.h"
#include "common.h"

int main(int argc,char *argv[])
{
	if(check_operation_type(argv)==e_encode)
	{
		printf("Selected Encoding.\n");
		EncodeInfo encInfo;
		if(read_and_validate_encode_args(argv,&encInfo)==e_success)
		{
			printf("Validation of arguments is success.\n");
			if(do_encoding(&encInfo)==e_success)
			{
				printf("Encoding success.\n");
			}	
			else
			{
				printf("Error : Unable to perform encoding.\n");
			}
		}	
		else
		{
			printf("Error : Validation of arguments failed\n");
		}
	}	
	else if(check_operation_type(argv)==e_decode)
	{
		printf("Selected Decoding\n");
		DecodeInfo decInfo;
		if(read_and_val_decode_args(argv,&decInfo)==e_success)
		{
			printf("Validation of arguments success.\n");
			if(do_decoding(&decInfo)==e_success)
			{
				printf("Decoding succesfully done.\n");
			}
			else
			{
				printf("Error : Unable to decode the data\n");
			}
		}
		else
		{
			printf("Error : Arguments validation failed.\n");
		}
	}
	else if(check_operation_type(argv)==e_unsupported)
	{
	printf("Error : unsupported option\n");
	}	
}
OperationType check_operation_type(char *argv[])
{
	if(!strcmp(argv[1],"-e"))
	{
		return e_encode;
	}
	else if(!strcmp(argv[1],"-d"))
	{
		return e_decode;
	}
	else
	{
		return e_unsupported;
	}
}
Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
	if(argv[2] != NULL)
	{
		if(!strcmp(strchr(argv[2],'.'),".bmp"))
		{
			encInfo->src_image_fname=argv[2];
		}
		else
		{
			return e_failure;
		}
	}
	else
	{
		return e_failure;
	}
	if(argv[3] != NULL)
	{
		encInfo->secret_fname=argv[3];
		strcpy(encInfo->extn_secret_file,strchr(argv[3],'.'));
	}
	else
	{
		return e_failure;
	}
	if(argv[4] != NULL)
	{
		if(!strcmp(strchr(argv[4],'.'),".bmp"))
		{
		encInfo->stego_image_fname=argv[4];
		}
		else
		{
			int opt;
back :
			printf("The stego file name is incompatible.\nPLEASE SELECT A OPTION : \n1.Convert to compatible file\n2.Exit\nOPTION -->  ");
			scanf("%d",&opt);
			if(opt==1)
			{
				encInfo->stego_image_fname=strcat(argv[4],".bmp");
			}
			else if(opt == 2)
			{
				exit(1);
			}
			else
			{
				printf("Invalid option. Please select correct option.\n");
				goto back;
			}
		}
	}
	else
	{
		encInfo->stego_image_fname="default_stego.bmp";
	}
	return e_success;
}

Status read_and_val_decode_args(char *argv[],DecodeInfo *decInfo)
{
	if(argv[2]!=NULL)
	{
		if(!strcmp(strchr(argv[2],'.'),".bmp"))
		{
			decInfo->src_fname=argv[2];
		}
		else
		{
			return e_failure;
		}
	}
	if(argv[3]!=NULL)
	{
		decInfo->dest_name=argv[3];
	}
	else
	{
		decInfo->dest_name="default_output";
	}
	return e_success;
}
