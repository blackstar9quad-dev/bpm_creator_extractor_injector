#include <SDL2/SDL.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdbool.h>
#include <stdbool.h>



int interactor(SDL_Event *event ,  int bitpixel_count , struct pixel_rgb_value *pixel_data ){
	printf("NOW IN THE INTERACTOR \n");
	bool value =  true ;

	int i = 0;
	while(i<bitpixel_count){
		while(SDL_PollEvent(event) != 0){
			if(event->type == SDL_QUIT){
				value =  false ;
				break;
			}else if(event->type = SDL_MOUSEBUTTONDOWN){
				if(event->button.button == SDL_BUTTON_LEFT){
					printf("the left mouse has been pressed \n");
					printf("positon of the mouse ( x : %d ) ( y : %d ) \n",event->button.x ,  event->button.y);
					char choice[10] ;
					if(!fgets(choice,sizeof(choice),stdin)){
						perror("INPUT ERROR \n");
						return -1;
					};

					if(strcmp(choice,"n") == 0){
						printf("VALUE NOT SAVED \n");
						continue;
					}else if(strcmp(choice,"y") == 0){

						pixel_data[i].red = event.button.x;
						pixel_data[i].green =  event.button.y;
						pixel_data[i].blue = 128;

						printf("VALUES SAVED IN THE INDEX : %d ",i);

						i+=1;

						break;
					};
				};
				break;
			}
		};
	};

	return 1;
};

int gradient_creator(SDL_Renderer *renderer , int height , int width){
	printf("Creating the gradient \n");
	for(int i=0 ; i<height ; i= i+4){
		printf("CREATING COLOR FOR ROW %d",i);
		for(int j=0 ; j<width ; j=j+4){
			printf("FILLING THE ROW %d" , i);
			if(SDL_SetRenderDrawColor(renderer,i,j,128,255) < 0){
				perror("COLOR SETTER ERROR \n");
				return -1;
			};
			SDL_Rect rect = {0+i , 0+j , 4 ,4};

			printf("rect created \n");

			if(SDL_RenderFillRect(renderer,&rect) <0){
				perror("RECTANGOLE CREATIONN EERROR \n");
				return -1;
			};
		};

		printf("row filled \n");
	};
	SDL_RenderPresent(renderer);
	printf("GRID MADE \n");
};

int window_creator(SDL_Window **window , int height , int width , char name[100] ){
	*window = SDL_CreateWindow(name,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,0);
	if(!*window){
		perror("WINDOW CREAATION ERROR\n");
		return -1;
	};

	return 1;
};

int renderer_creator(SDL_Renderer **renderer , SDL_Window *window ){
	*renderer =  SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	if(!*renderer){
		perror("RENDERER CREATION ERROR \n");
		return -1;
	};

	printf("RENDERER INFO SAVED AND RENDERER OBJECT CREATED \n");

	return 1;

};

int parser(int argc , char *args[] ,  int *height , int *width , char name[100]){
	printf("PARSING THE COMMAND \n");

	for(int i =0  ; i<argc ; i++){
		if(strcmp(args[i],"--W") == 0){
			char *width_value= args[i+1] ;
			*height = strtol(width_value,NULL,10);
			printf("WIDTH SAVED \n");
			continue;
		}else if(strcmp(args[i],"--H") == 0){
			
			char *height_value =  args[i+1];
	
			*width =  strtol(height_value,NULL,10);
			printf("HEIGHT SAVED \n");
			continue;
		}else if(strcmp(args[i],"--name") == 0){
			strncpy(name,args[i+1],99);
			name[sizeof(args[i+1] + 1)] == '\0';

			printf("NAME SAVED \n");
			continue;
		};
	};

	printf("PARSING COMPLETE \n");
	return 1;
};



int gradient_maker(int height , int width  , uint32_t total_pixel, uint32_t bitpixel_count){
	SDL_Init(SDL_INIT_VIDEO);
	printf("SDL INITLIZED \n");
	//int height = 200 , width = 200 ;   // wouild come from the bmp file 
	char name[] = "gradient";

	pixel_data =  (struct pixel_rgb_value *)malloc(bitpixel_count);

    /*	if(parser(argc , args, &height , &width , name)<0){
		printf("OPERATION FAILED \n");
		return -1;
	};*/

	SDL_Window *window ;

	int result =  window_creator(&window,height,width,name);
	if(result<0){
		printf("OPERATION FAILED \n");
		return -1;
	};

	SDL_Renderer *renderer;
	if(renderer_creator(&renderer ,window) < 0){
		printf("OPERATION FAILED \n");
		return -1;
	};
	printf("OPERATION SUCCESSFUL \n");

	if(gradient_creator(renderer ,  height ,  width) < 0){
		printf("OPERATION FAILED \n");
		return -1;
	};

	SDL_Event event ;

	if(interactor(&event) < 0){
		printf("OPERATION FAILED \n");
		return -1;
	};

	sleep(100);

	    // Clean up
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
	return -1 ;

};
