#include <SDL2/SDL.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



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



int main(int argc , char *args[]){
	SDL_Init(SDL_INIT_VIDEO);
	printf("SDL INITLIZED \n");
	int height , width ;
	char name[100];

	if(parser(argc , args, &height , &width , name)<0){
		printf("OPERATION FAILED \n");
		return -1;
	};

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

	sleep(100);

	    // Clean up
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
	return -1 ;

};
