#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#define WIDTH 800
#define HEIGHT 600

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  if (!SDL_CreateWindowAndRenderer("Hello World",
                                   WIDTH,
                                   HEIGHT,
                                   SDL_WINDOW_RESIZABLE,
                                   &window,
                                   &renderer)) {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  texture = SDL_CreateTexture(renderer,
                              SDL_PIXELFORMAT_XRGB8888,
                              SDL_TEXTUREACCESS_STREAMING,
                              WIDTH,
                              HEIGHT);

  if (!texture) {
    SDL_Log("Couldn't create streaming texture: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS; /* end the program, reporting success to the OS. */
  }
  return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate) {
  uint32_t *pixels;
  int pitch;

  if (!SDL_LockTexture(texture, NULL, (void **)&pixels, &pitch)) {
    SDL_Log("Couldn't lock texture: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  for (size_t i = 0; i < WIDTH * HEIGHT; i++) {
    pixels[i] = i;
  }

  SDL_UnlockTexture(texture);
  SDL_RenderTexture(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);

  return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result) {}
