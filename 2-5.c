// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>



typedef struct
{
	char** items;
	int index;
} stringVect;






void initialize(stringVect* strV)
{
	strV->index = 0;
	strV->items = malloc(sizeof(char));

}


void addString(stringVect* ptr, char* buffer)
{
	size_t len = strlen(buffer) + 1;
	ptr->items[ptr->index] = malloc(len);
	strncpy(ptr->items[ptr->index++], buffer, len);
}


void print(stringVect* strV, int index)
{
	printf(
		"the address at index %d is %p\nthe value at index %d is %s", index, &(strV->items[index]), index, strV->items[index]
	);
}


//we'll free all the memory 
void freeMemory(stringVect* strV)
{
	for (int i = 0; i < strV->index; i++)
	{
		free(strV->items[strV->index]);
	}
}


//Stage 1
//add / delete line
//edit line
//print line numbers
//save to file
//load from file

char* return_string(stringVect* ptr, int index)
{
	return ptr->items[index];
}

char* append_char(stringVect* ptr, int i, char c)
{
	//create a temporary ptr that reallocates the memory
	 //add c and '\0' to temporary,
	 //set ptr to temporary and free temp

	 //last is at the index of where the '\0' is
	int last = strlen(ptr->items[i]);
	//we do +2 to add c and '\0'
	char* temp = realloc(ptr->items[i], last);
	temp[last++] = c;
	temp[last] = '\0';

	ptr->items[i] = temp;
	return ptr->items[i];
	free(temp);
}

char* remove_last_char(stringVect* ptr, int i)
{
	//perform the reverse of append_char and get the index of the last element of the string, and replace it with '\0'
	int last = strlen(ptr->items[i]) - 1;
	char* temp = realloc(ptr->items[i], last);
	temp[last] = '\0';
	ptr->items[i] = temp;
	return ptr->items[i];
	free(temp);
}

void swapString(stringVect* ptr, int loc1, int loc2)
{

	size_t len1 = strlen(ptr->items[loc1]) + 1;
	size_t len2 = strlen(ptr->items[loc2]) + 1;
	//need to store one strings data in a temporary pointer so it doesnt get lost, we'll store string1 in a temp 

	//4 btyes are already in play
	char* temp = malloc(len1 - 4);

	//temp is now string1 
	strncpy(temp, ptr->items[loc1], len1);
	//string 2 has enough space for string1
	char* temp1 = realloc(ptr->items[loc2], len1);

	//string1 has enough space for string2

	char* temp2 = realloc(ptr->items[loc1], len2);

	ptr->items[loc1] = temp2;
	ptr->items[loc1] = ptr->items[loc2];

	ptr->items[loc2] = temp1;
	ptr->items[loc2] = temp;

	temp = NULL;
	temp1 = NULL;
	temp2 = NULL;
	free(temp);
	free(temp1);
	free(temp2);

}

//must take in stringVect* instead since that is the value being changed
void customRealloc(stringVect* ptr, char* string, int location)
{
	char* temp = realloc(ptr->items[location], strlen(string) + 1);
	ptr->items[location] = temp;
	strncpy(ptr->items[location], string, strlen(string) + 1);
}

//should tweak so it deletes like a linked list
void deleteString(stringVect* ptr, int location)
{
	int itr = ptr->index - 1;
	char* temp = malloc( strlen(ptr->items[ptr->index-1]) + 1);
	strncpy(temp, ptr->items[ptr->index-1], strlen(ptr->items[ptr->index-1]) + 1 );

	while (itr != location)
	{
		int i = itr - 1;
		//should overwrite the empty buffer to the iterator I value;
		customRealloc(ptr, ptr->items[i], ptr->index-1);

		//problematic call of customRealloc
		customRealloc(ptr, temp, i);
		
		//uses strncpy because customRealloc only takes in stringVect* as first parameter
		strncpy(temp, ptr->items[ptr->index-1], strlen(ptr->items[ptr->index-1]) + 1);
		i--;
		itr--;
	}
	ptr->items[ptr->index-1] = NULL;
	free(ptr->items[ptr->index - 1]);
	ptr->index--;
}
void printAll(stringVect* strV)
{
	for (int i = 0; i < strV->index; i++)
	{
		printf("Address at index %d:%p\nValue at index %d: %s\n", i, &(strV->items[i]), i, strV->items[i]);
		printf("The size of the string at index %d: %d\n\n", i, strlen(strV->items[i]));
	}

}
void save_to_file(stringVect* ptr)
{
	FILE* fptr;
	fptr = fopen("C:\\Users\\jjthu\\source\\repos\\LinkedList\\textEditor\\writtenOutput\\output.txt", "w");
	char* string = "Hello World";

	// 3. Always check if the file opened successfully
	if (fptr == NULL) {
		printf("Error opening the file!\n");
		return 1; // Exit with error code
	}

	// 4. Write data to the file
	fprintf(fptr, string);

	// 5. Close the file to free system resources
	fclose(fptr);

	printf("Data successfully written to output.txt\n");
	return 0;

}
char* duplicate_string(const char* src)
{
	char* returnedString = src;
	return returnedString;
}


typedef struct {
	SDL_Window* mWindow;
	bool mRunning;
	SDL_Renderer* mRenderer;
	int wM, hM;
	TTF_Font* mfont;
	SDL_FRect mDst;

}SDLApplication;


void loadFont(SDLApplication* sdlP)
{
	sdlP->mfont = TTF_OpenFont("font/Rockwell.otf", 20);
}

SDL_Texture* renderText(SDLApplication* sdlP,char* string)
{

	SDL_Color white = { 255, 255, 255, 255 };

	SDL_Surface* surface =
		TTF_RenderText_Blended(sdlP->mfont, string, 0, white);

	if (!surface)
	{
		printf("%s\n", SDL_GetError());
		return 1;
	}

	float width = (float)surface->w;
	float height = (float)surface->h;
	SDL_Texture* texture =
		SDL_CreateTextureFromSurface(sdlP->mRenderer, surface);

	SDL_DestroySurface(surface);

	SDL_FRect dst = {
		50.0f,
		50.0f,
		width,
		height
	};

	sdlP->mDst = dst;

	SDL_SetRenderDrawColor(sdlP->mRenderer, 30, 30, 30, 255);
	return texture;
}
void render(SDLApplication* sdlP)
{
	SDL_RenderClear(sdlP->mRenderer);
	SDL_RenderTexture(sdlP->mRenderer, renderText, NULL, &(sdlP->mDst));
	SDL_DestroyTexture(renderText);
	TTF_CloseFont(sdlP->mfont);
}



void initializeSDL3(SDLApplication* sdlP)
{
	SDL_Init(SDL_INIT_VIDEO);
	sdlP->mRunning = false;
	int w = 640, h = 480;
	sdlP->wM = w;
	sdlP->hM = h;
	sdlP->mWindow = SDL_CreateWindow("SDL3 window", w, h, SDL_WINDOW_OPENGL);

	if (sdlP->mWindow == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	if (!TTF_Init()) {
		printf("TTF Init failed: %s\n", SDL_GetError());
		return 1;
	}

}


void sdlRunning(SDLApplication* sdlP)
{
	SDL_Renderer* renderer = SDL_CreateRenderer(sdlP->mWindow, NULL);
	if (!renderer)
	{
		printf("Renderer creation failed: %s\n", SDL_GetError());
		return 1;
	}


	sdlP->mRenderer = renderer;

	Uint64 lastTime = SDL_GetTicks();
	renderText(sdlP, '|');
	while (!sdlP->mRunning)
	{
		SDL_Event event;

		Uint64 currentTime = SDL_GetTicks();
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				sdlP->mRunning = true;
			}
		}
		float deltaTime = (float)(currentTime - lastTime) / 1000.0f;
		SDL_Log("%f", currentTime);
		lastTime = currentTime;
		//every second you want the cursor the "blink", this should be done by defining the delay to be one second, 
		//then on the draw cursor function, calculate the time, if the time is greater than or equal to delay, perform action, then reset the delta time to repeat.

		SDL_RenderPresent(sdlP->mRenderer);
		render(sdlP);
		//writeText(sdlP);
	}


	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(sdlP->mWindow);
	TTF_Quit();
	SDL_Quit();
}
int main() {
	int counter = 0;
	char buffer[256];
	stringVect strV;
	SDLApplication sdlA;
	SDLApplication* sdlP = &sdlA;
	stringVect* strVp = &strV;
	initialize(strVp);
	//while (counter < 4)
	//{
	//	printf("Enter a string:\n");

	//	if (fgets(buffer, sizeof(buffer), stdin) != NULL)
	//	{
	//		addString(strVp, buffer);
	//	}

	//	counter++;
	//}
	//printAll(strVp);
	//printf("\n\n");
	initializeSDL3(sdlP);
	sdlRunning(sdlP);
}
