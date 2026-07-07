#include "Engine.h"


using namespace nu;


int main()
{
    // INITALIZATION
    nu::Renderer renderer;
    renderer.Initialize("Game Engine", 1920, 1024);

    nu::Input input;
    input.Initialize();

    //std::cout << sizeof(Vector2) << std::endl;
    Vector2 vel{ 0.5f, 0.0f };

    std::vector<Vector2> v;

    for (int i = 0; i < 300; i++)
    {
        v.push_back({ nu::RandomFloat(1280), nu::RandomFloat(1024) });
    }
    
    bool quit = false;

    while (!quit) 
    {
        
        SDL_Event event;
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_EVENT_QUIT) 
            {
                quit = true;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE)
            {
                quit = true;
            }
        }

        input.Update();

        renderer.SetColor(0.0f, 0.0f, 0.0f);
        renderer.Clear();

        for (int i = 0; i < v.size(); i++) 
        {
            renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat());

            v[i] = v[i] + vel;
            renderer.DrawPoint(v[i].x, v[i].y);
        }

        renderer.SetColor(1.0f, 1.0f, 1.0f);
        renderer.DrawFillRect(input.GetMousePosition().x - 20, input.GetMousePosition().y - 20, 40, 40);

        for (int i = 0; i < 1000; i++)
        {
            renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat());
            renderer.DrawRect(rand() % 1280, rand() % 1024, rand() % 256, rand() % 256);
        }

        


        renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat()); // Set render draw color to green
        renderer.DrawFillRect(40, 40, 40 ,40); // Render the rectangle

        

        renderer.Present(); // Render the screen
    }

    renderer.Shutdown();
    
    return 0;
}

