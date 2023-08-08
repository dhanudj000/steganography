#include "types.h"
typedef struct _DecodeInfo
{
	/*stego image info*/
	char *src_fname;
	FILE *fptr_src_file;
	uint secret_file_size;

	/*output file info*/
	char *dest_name;
	char *secret_file_exn;
	FILE *fptr_dest_file;
	uint secret_file_exn_size;

}DecodeInfo;
 /*read and validation of decoding arguments*/
  Status read_and_val_decode_args(char *argv[],DecodeInfo *decInfo);  

  /* starting decoding*/
  Status do_decoding(DecodeInfo *decInfo);

  /* Opening stego file */
  Status open_stego_file(DecodeInfo *decInfo); 
 
  /* Decoding magic string */
 Status decode_magic_string(char *magic_string,DecodeInfo *decInfo) ;

 /* Decoding image bytes to original data */
 Status decode_bytes_to_data(FILE *fptr_src,char *str,int size);
 
 /* Decoding extension size */
 Status decode_exn_size(DecodeInfo *decInfo);

 /* Decoding size from the 32 bytes */
 Status decode_lsb_to_size(int *size,char *str);  

 /* Decoding exn file*/
 Status decode_sec_file_exn(DecodeInfo *decInfo) ; 

 /* Opening output file */
 Status open_output_file(DecodeInfo *decInfo) ;

 /* Decode size of secret file data */
 Status read_secret_data_size(DecodeInfo *decInfo)  ; 
  
 /* Decoding our required secret file data */
Status decode_secret_data(DecodeInfo *decInfo);  
