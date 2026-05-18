#include <SDL2_	SDL.H>
#include <string.h>
#include "../bmp_component/bmp_structure.h"


int randomizor( struct bmp_pixeldata *user_pixel_data , int total_pixel){
	printf("GENERATING RANDOM COLOR FROM YOUR PALLET .. \n");
	int random_num ;
	
	for(int i =0 ; i< total_pixel ;  i++){
        	random_num = rand() % (1<<bitpixel_count) ;
		user_pixel_data->pixel_data[i] = random_num ;
	};

	printf("USER PIXEL TAKEN IN THE FROM THE PALLET FOR IMAGE CONSIDERATION \n");

	return 1;


};

int manual_input( struct bmp_pixeldata *user_pixel_data , int total_pixel){
	char choice[1024];
	printf("STARTING THE MANUAL CHOOSING \n");

	for(int i = 0 ; i<total_pixel ; i++){
        	if(!fgets(choice,sizeof(choice),stdin)){
         		perror("INPUT ERROR \n");
         		return -1;
        	};

		uint8_t num ;

		num = (uint8_t *)strtol(choice,NULL,10);

		user_pixel_data->pixel_data[i] = num;

	};

	printf("OPEARATION SUCCESSFUL | user input table created \n");

	return 1;	
};

void pallet_printer(uint32_t bitpixel_count){
	printf("THE COLOR GRADIETN LIST \n");
	for(int i = 0 ; i <0 ; i++){
		printf("red : %d,
			green : %d,
blue: 128 \n"
	};

	printf("----------------------------------------------------------------------------------")

};


int user_pixel_creator( uint8_t *user_pixel_data){
	char choice[10] ;

	printf("STARTING THE CRETION OF THE USER PIXEL DATA \n");
	printf("DO U WANNA CREATE AT RANDOM OR INPUT MANUALY (r/m) \n");
	if(!fgets(choice,sizeof(choice),stdin)){
		perror("INPUT ERROR \n");
		return -1;
	};

	if(strcmp(choice,"r") == 0){
		if(randomizor(user_pixel_data) <0){
			printf("OPERATION FAILED \n");
			return -1 ;
		};

		printf("OPERATION SUCCESSFUL \n");
		return 1;

	}else if(strcmp(choice,"m") == 0){
		if(manual_input(user_pixel_data) <0){
			printf("OPERATION FAILED \n");
			return -1;
		};

		printf("OPEARTION SUCCESSFUL \n");
		return 1;
	};
};

int one_bit_pixel(uint8_t *user_pixel_data , int total_bits , struct  bmp_pixeldata *pixel_data_holder){
	number_of_bytes =  (total_bits + 7) /  8 ;

	pixel_data_holder->pixel_data = (uint8_t *) malloc(number_of_bytes);

	uint8_t *pixel_data  = pixel_data_holder->pixel_data ;

	memset(pixel_data , 0 , number_of_bytes);


	int byte_index ;
	int bit_index ;

	for(int i = 0 ; i < total_bits ; i++){
		byte_index =  i / 8 ;
		bit_index  = i % 8 ;

		if(user_pixel_data[i] == 1){
			pixel_data[byte_index] |= (1<<bit_index);
			printf("bit flipped \n");
		};
	};

	printf("OPERATION PERFORMED \n");

	return 1;

};

int two_bit_pixel(uint8_t *user_pixel_data , int totalpixel , struct bmp_pixeldata *pixel_data_holder)
{
	int total_bits =  total_pixel *  2 ;
	int number_of_bytes =  (total_bits+7) / 8 ; 

	pixel_data_holder->pixel_data =  (uint8_t *) malloc(number_of_bytes);
	uint8_t *pixel_data =  pixel_data_holder->pixel_data ;

	memset(pixel_data , 0 , number_of_bytes );

	int bit_index , slot , shift ;

	for(int i =0 ; i < total_pixel ; i++){
		byte_index =  i / 4 ;

		slot = i % 4 ;       //out of the 4 slots wehich we are working onn

		shift =  slot * 2 ; // this the start bit 

		pixel_data[byte_index] |= (user_pixel_data[i] << shift);

		printf("slot edit performed \n");
		
	};

	printf("OPRATION COMPLETE \n");

	return 1;
};

int four_bit_pixel(uint8_t *user_pixel_data , int totalpixel , struct bmp_pixeldata *pixel_data_holder ){
	int total_bits = totalpixel * 4 ;
	int number_of_bytes ; 
	number_of_bytes = (total_bits+7)/8;

	pixel_data_holder->pixel_data =  (uint8_t *)malloc(number_of_bytes);

	uint8_t *pixel_data  =  pixel_data_holder->pixel_data;

	memset(pixel_data,0,number_of_bytes);

	for(int i = 0 ; i<=totalpixel ; i++){
		byte_index = i / 2 ;

		slot =  i % 2 ;

		shift =  slot * 4 ;

		pixel_data[byte_index] |=  (user_pixel_data << shift);

		printf("SLOT CHANGED \n");
	};

	printf("OPERATION COMPLETED \n");

	return 1 ;
};

int eight_bit_pixel(uint8_t *user_pixel_data ,  int totalpixel , struct bmp_pixeldata *pixel_data_holder){
	int number_of_bytes =  totalpixel ;

	pixel_data_holder->pixel_data =  (uint8_t *)malloc(number_of_bytes);

	uint8_t *pixel_data = pixel_data_holder->pixel_data
	memeset(pixel_data,0,number_of_bytes);

	for(int i = 0 ; i<totalpixel ; i++){
		pixel_data =  user_pixel_data[i];

		printf("PIXEL  DATA SAVED \n");
	};

	printf("OPERATION PERFORMED \n");

	return -1;
};

int user_pixel_input(uint8_t *user_pixel_data , uint32_t  bitcount_pixel ,  struct bmp_infoheader infoheader , struct  bmp_pixeldata *pixel_data_holder){
	printf("ENTER THE PIXEL DATA");
	int presentor ;

	uint32_t width , height ;
	width =  bmp_infoheader.image_width;
	height =  bmp_infoheader.image_height ; 

	uint32_t  total_pixel ;
	total_pixel =  width *  height ;


	presentor =  gradient_maker(height , width , total_pixel);
	if(presentor<0){
		printf("OPERATION FAILED \n");
		return -1 ;
	};

	if(pallet_printer() <0){
		printf("OPERATION FAILED \n");
		return -1;
	};

//before this we make the user choose the colors and we create the pallet table and then now after this we show the pallet table and then user can define the it's own pixel data 
//

	if(user_pixel_creator(user_pixel_data) <0){
		printf("OPERATION  FAILED \n");
		return -1;
	};


	uint8_t spixel ;
	char input_pixel[100];
	printf("PIXEL DATA CREATED \n");


	int total_bits ;
	if(bitcount_pixel == 1){  // need to change the total_pixel name to total_bits ;
		int  total_bits  =  widht * height * bitcount_pixel ; 
		result = one_bit_pixel(user_pixel_data, total_bits, pixel_data_holder);
		if(result<0){
			printf("OPERATION FAILED \n");
			return -1;
		};
		printf("OPERATION SUCCESSFUL \n");
	}else if(bitcount_pixel == 2 ){
		int  total_bits  =  widht * height / 2   ; 
		result = two_bit_pixel(user_pixel_data , total_pixel );
		if(result<0){
			printf("OPERATION FAILED \n");
			return -1;
		};
		printf("OPERATION SUCCESSFUL \n");
	}else if(bitcount_pixel == 4 ){
		result = four_bit_pixel(user_pixel_data ,  total_pixel );
		if(result<0){
			printf("OPERATION FAILED \n");
			return -1;
		};
		printf("OPERATION SUCCESSFUL \n");
	}else if(bitcount_pixel == 8 ){
		result = eight_bit_pixel(user_pixel_data ,  total_pixel);
		if(result<0){
			printf("OPERATION FAILED \n");
			return -1;
		};
		printf("OPERATION SUCCESSFUL \n");
	}else{
		printf("16 / 24 / 32 BIT  color scheme understand dev \n");
		return -1 ;
	};

	printf("PIXEL DATA HAS BEEN MADE \n");

	return 0;

};

int bmp_dibheader_creator(uint32_t bitcount_pixel , struct bmp_infoheader *bmp_infoheader){
	printf("CREATING THE DIB HEADER \n");

	char usr_input[100];
	uint32_t  width , height ;

	if(!fgets(usr_input,sizeof(usr_input,stdin))){
			perror("INPUT ERROR \n");
			return -1;
	};
	width  = strtol(usr_input,NULL,10);

	if(!fgets(usr_input,sizeof(usr_input,stdin))){
			perror("INPUT ERROR \n");
			return -1;
	};
	height =  strtol(usr_input,NULL,10);

	bmp_infohrader->dib_size = 40 ;
	bmp_infoheader->image_width = width ;
	bmp_infoheader->image_height = height ;
	bmp_infoheader->bmp_planes = 1 ;
	bmp_infoheader->bmp_compression = 0;
	bmp_infoheader->bmp_bitdepth = bitcount_pixel;
	bmp_infoheader->bmp_xppm = 0;
	bmp_infoheader->bmp_yppm  = 0 ;
	bmp_infoheader->bmp_colorused = 0;
	bmp_infoheader->bmp_colorimportant = 0;

	printf("DIB HEADER SAVED \n");
};


int main(){
	char usr_input[1024];
	int result ;
        struct  bmp_pixeldata pixel_data_holder;

	uint32_t bitcount_pixel;

	printf("STARTING THE PROCESS .... \n");

	printf("ENTER THE SIZE PER BIT OF THE PIXEL \n");
	if(!fgets(usr_input,sizeof(usr_input),stdin)){
		perror("INPUT ERROR \n");
		return -1;
	};

	bitcount_pixel = strtol(usr_input,NULL,10);
	if(bitcount_pixel == usr_input){
		perror("conversion error \n");
		return -1;
	};

	int totalpixel =  height * width * bitcount_pixel ;


	struct bmp_infoheader bmp_infoheader ;
	result = bmp_dibheader_creator(bitcount_pixel  , &bmp_infoheader);
	if(result <0){
		printf("OPERATION FAILED \n");
		return -1;
	};
	printf("operation completed \n");

	user_pixel_data = (uint8_t *)malloc(height * width)
	result =  user_pixel_input(user_pixel_data , bitpixel_count , bmp_infoheader, &pixel_data_holder);
};

