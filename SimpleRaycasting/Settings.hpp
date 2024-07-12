#ifndef _RCSettings
#define _RCSettings

#define BlockSize 48
#define PI 3.14159265

#define WindowSizeX 1024
#define WindowSizeY 768

// Raycasting
#define StandardJump        BlockSize / 10
#define RayJumps            32 
#define MaxRayLenght        BlockSize / 10 * RayJumps
#define RayCounter          128
#define HalfRayCounter      RayCounter / 2
#define FOV                 PI / 3 // Field of View
#define HalfFOV             FOV / 2
#define DeltaRayRadAngle    FOV / RayCounter    
#define DrawWidth           WindowSizeX / RayCounter

// Map
#define WorldX 18
#define WorldY 12

static short WorldMap[WorldY][WorldX] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
#endif // !_RCSettings