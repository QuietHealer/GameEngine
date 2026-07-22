#include "engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"

#include <iostream>
#include <vector>
#include <Scene.h>

using namespace nu;


int main()
{
    // get current working directory
    std::cout << "Directory Operations:\n";
    std::cout << "Working directory: " << nu::GetWorkingDirectory() << "\n";

    // set working directory (current working directory + "Assets")
    std::cout << "Setting directory to 'Assets'...\n";
    nu::SetWorkingDirectory("Assets");
    std::cout << "New directory: " << nu::GetWorkingDirectory() << "\n\n";

    // get filenames in the working directory
    std::cout << "Files in Directory:\n";
    auto filenames = nu::GetFilesInDirectory(nu::GetWorkingDirectory());
    for (const auto& filename : filenames)
    {
        std::cout << filename << "\n";
    }
    std::cout << "\n";

    // get filename info
    if (!filenames.empty())
    {
        // get filename
        std::string str = nu::GetFilename(filenames[0]);
        std::cout << "Filename: " << str << "\n";

        // get extension
        str = nu::GetFileExtension(filenames[0]);
        std::cout << "Extension: " << str << "\n";

        // get filename no extension
        str = nu::GetFilenameNoExtension(filenames[0]);
        std::cout << "Filename No Extension: " << str << "\n\n";
    }

    // read and display text file
    std::cout << "Text File Reading:\n";
    std::string str;
    if (nu::ReadTextFile("test.txt", str))
    {
        std::cout << str << "\n";
    }

    // write to text file
    std::cout << "Text File Writing:\n";
    nu::WriteTextFile("test.txt", "Hello, World!", true);
    if (nu::ReadTextFile("test.txt", str))
    {
        std::cout << str << "\n";
    }
    // INITALIZATION
    Engine::Get().Initialize();

    // create audio system
    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    std::vector<FMOD::Sound*> sounds;

    FMOD::Sound* sound = nullptr;
    audio->createSound("whistle.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("alert.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("error.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("oof.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("hee-hee.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    Scene scene;

    PlayerDesc playerDesc;
    playerDesc.name = "Player";
    playerDesc.model = assets::playerModel;
    playerDesc.transform = Transform{ Vector2{ 640.0f, 512.0f}, 0.0f, 15.0f };
    playerDesc.speed = 2000.0f;

    //Player* player = new Player{2000.0f, Transform{ Vector2{ 640.0f, 512.0f}, 0.0f, 50.0f } ,  model  };
    Player* player = new Player{playerDesc};
    scene.AddActor(player);

    for (int i = 0; i < 20; i++)
    {
        EnemyDesc enemyDesc;
        enemyDesc.name = "Enemy";
        enemyDesc.model = assets::playerModel;
        float x = nu::RandomFloat((float)Engine::Get().GetRenderer().GetWidth());
        float y = nu::RandomFloat((float)Engine::Get().GetRenderer().GetHeight());
        enemyDesc.transform = Transform{ Vector2{ x, y }, 90.0f, 10.0f };
        enemyDesc.speed = 2000.0f;

        Enemy* enemy = new Enemy{ enemyDesc };

        //Enemy* enemy = new Enemy{ 2000.0f, Transform{ Vector2{ nu::RandomFloat((float)nu::engine.GetRenderer().GetWidth()), (float)nu::RandomFloat(nu::engine.GetRenderer().GetHeight()}, 90.0f, 10.0f} ,  model };
        scene.AddActor(enemy);
    }

    // Photoshop
    std::vector<Vector2> points;

    // MANE LOOP
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


        Engine::Get().Update();
        scene.Update(Engine::Get().GetTime().GetDeltaTime());
        audio->update();

        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_1))
        {
            audio->playSound(sounds[0], nullptr, false, nullptr);
        }

        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_2))
        {
            audio->playSound(sounds[1], nullptr, false, nullptr);
        }
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_3))
        {
            audio->playSound(sounds[2], nullptr, false, nullptr);
        }
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_4))
        {
            audio->playSound(sounds[3], nullptr, false, nullptr);
        }
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_5))
        {
            audio->playSound(sounds[4], nullptr, false, nullptr);
        }
        
        Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        Engine::Get().GetRenderer().Clear();

        if (Engine::Get().GetInput().GetButtonPressed(Input::MouseButton::Left))
        {
            points.push_back(Engine::Get().GetInput().GetMousePosition());
        }

        if (Engine::Get().GetInput().GetButtonDown(Input::MouseButton::Left))
        {
            if (points.empty())
            {
                points.push_back(Engine::Get().GetInput().GetMousePosition());
            }
            else
            {
                Vector2 v = points.back() - Engine::Get().GetInput().GetMousePosition();
                if (v.Length() > 10.0f)
                {
                    points.push_back(Engine::Get().GetInput().GetMousePosition());
                }
            }
        }

        if (Engine::Get().GetInput().GetButtonPressed(Input::MouseButton::Right))
        {
            if (points.empty())
            {
                points.pop_back();
            }
        }
        
        Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        Engine::Get().GetRenderer().Clear();

        for (int i = 0; i < (int)points.size() - 1; i++) 
        {
            Engine::Get().GetRenderer().SetColor(RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat());
            Engine::Get().GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        scene.Draw(Engine::Get().GetRenderer());

        Engine::Get().GetRenderer().Present(); // Render the screen
    }
    
    return 0;
}

