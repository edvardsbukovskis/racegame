#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH (800)
#define WINDOW_HEIGHT (540)

// speed in pixels/second

#define MAXSPEED (8)


int main(void)
{
    // attempt to initialize graphics and timer system
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("Racegame Win",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT,0);
    if (!win)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
	    return 1;
    }

    // create a renderer which sets up the graphics hardware
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!rend)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // load the image into memory
    SDL_Surface* surface = IMG_Load("resources/car.png");
    if (!surface)
    {
        printf("error creating surface\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // load the image data into the graphics hardware memory
    SDL_Texture* carTexture = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    if (!carTexture)
    {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    //create background image
    surface = IMG_Load("resources/racetrack.jpg");
    SDL_Texture *bkgTexture = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    // struct to hold the position and size of the sprite
    SDL_Rect dest;

    // get and scale the dimensions of texture
    SDL_QueryTexture(carTexture, NULL, NULL, &dest.w, &dest.h);
    dest.w /= 18;
    dest.h /= 18;

    // start sprite in center of screen
    float x_pos = (WINDOW_WIDTH - dest.w) -50 ;
    float y_pos = (WINDOW_HEIGHT - dest.h) - 150 ;

    // keep track of which inputs are given
    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;

    float speed = 0;
    float acc = 0.05;
    float dec= 0.03;
    float angle = 0;
    float rotateSpeed =0.15;
    

    // set to 1 when window close button is pressed
    int close_requested = 0;
    
    // animation loop
    while (!close_requested)
    {
        // process events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                close_requested = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    up = 1;
                    speed +=acc;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    left = 1;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    down = 1;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    right = 1;
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    up = 0;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    left = 0;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    down = 0;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    right = 0;
                    break;
                }
                break;
            }
        }

        // determine speed
        if (up && speed < MAXSPEED){
            if (speed < 0) speed += dec;
            else speed += acc;
        }
        if (down && speed > -MAXSPEED){
            if (speed > 0) speed -=dec;
            else speed -= acc;
        }
        if (!up && !down){
            if (speed - dec > 0) speed -=dec;
            else if (speed + dec < 0) speed +=dec;
            else speed = 0;
        }

        //determine angle of rotation
        if (right && speed != 0) angle += rotateSpeed * speed/MAXSPEED;
        if(left && speed != 0) angle -= rotateSpeed * speed/MAXSPEED;

        // update positions
        x_pos += sin(angle) * speed;
        y_pos -= cos(angle) * speed;

        // collision detection with bounds
        if (x_pos <= 0) x_pos = 0;
        if (y_pos <= 0) y_pos = 0;
        if (x_pos >= WINDOW_WIDTH - dest.w) x_pos = WINDOW_WIDTH - dest.w;
        if (y_pos >= WINDOW_HEIGHT - dest.h) y_pos = WINDOW_HEIGHT - dest.h;

        // set the positions in the struct
        dest.y = (int) y_pos;
        dest.x = (int) x_pos;
        
        // clear the window
        SDL_RenderClear(rend);

        SDL_RenderCopy(rend, bkgTexture, NULL, NULL);

        // draw the image to the window
        SDL_RenderCopyEx(rend, carTexture, NULL, &dest, angle*180/3.141592, NULL, SDL_FLIP_NONE);
        SDL_RenderPresent(rend);

        // wait 1/60th of a second
        SDL_Delay(1000/60);
    }
    
    // clean up resources before exiting
    SDL_DestroyTexture(carTexture);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}