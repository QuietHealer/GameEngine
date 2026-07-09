#include "Engine.h"


using namespace nu;


struct Transform
{
    Vector2 position;
    float rotation;
    float scale;
};

class Actor
{
public:
    Actor() = default;
    Actor(const Transform& transform) : m_transform{transform} {}

    void Update(float dt)
    {
        m_transform.position += (m_velocity * dt);
        m_velocity *= 0.987f;

        m_transform.position.x = Wrap(0.0f, 1920.0f, m_transform.position.x);
        m_transform.position.y = Wrap(0.0f, 1024.0f, m_transform.position.y);
    }

    void Draw(const Renderer& renderer) const
    {
        renderer.SetColor(1.0f, 1.0f, 1.0f);
        renderer.DrawFillRect(m_transform.position.x - (m_transform.scale * 0.5f), m_transform.position.y - (m_transform.scale * 0.5f), m_transform.scale, m_transform.scale);
    }

    const Transform& GetTransform() const { return m_transform; }
    void SetPosition(const Vector2& position) { m_transform.position = position; }
    void SetRotation(float rotation) { m_transform.rotation = rotation; }
    void SetScale(float scale) { m_transform.scale = scale; }

    void SetVelocity(const Vector2& velocity) { m_velocity = velocity; }
    const Vector2& GetVelocity() const  { return m_velocity; }

protected:
    Transform m_transform;
    Vector2 m_velocity{ 0, 0 };
};


int main()
{
    // INITALIZATION
    nu::Renderer renderer;
    renderer.Initialize("Game Engine", 1920, 1024);

    nu::Input input;
    input.Initialize();

    nu::Time time;

    Actor player{ Transform{ Vector2{ 640.0f, 512.0f}, 0.0f, 50.0f } };
    
    Vector2 position{ 640.0f, 512.0f };
    Vector2 velocity{ 0.0f, 0.0f };
    float speed = 800.4f;

    std::vector<Vector2> points;

    uint64_t ticks = SDL_GetTicks();
    uint64_t prevTicks;

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
        time.Tick();
        
        renderer.SetColor(0.0f, 0.0f, 0.0f);
        renderer.Clear();

        //if (input.GetKeyPressed(SDL_SCANCODE_Q)) std::cout << "pressed\n";
        //if (input.GetKeyDown(SDL_SCANCODE_Q)) std::cout << "down\n";
        //if (input.GetKeyReleased(SDL_SCANCODE_Q)) std::cout << "released\n";

        //if (input.GetButtonPressed(nu::Input::MouseButton::Left)) std::cout << "button pressed\n";
        //if (input.GetButtonDown(nu::Input::MouseButton::Left)) std::cout << "button pressed\n";
        //if (input.GetButtonReleased(nu::Input::MouseButton::Left)) std::cout << "button pressed\n";

        if (input.GetButtonPressed(Input::MouseButton::Left))
        {
            points.push_back(input.GetMousePosition());
        }

        if (input.GetButtonDown(Input::MouseButton::Left))
        {
            if (points.empty())
            {
                points.push_back(input.GetMousePosition());
            }
            else
            {
                Vector2 v = points.back() - input.GetMousePosition();
                if (v.Length() > 10.0f)
                {
                    points.push_back(input.GetMousePosition());
                }
            }
        }

        if (input.GetButtonPressed(Input::MouseButton::Right))
        {
            if (points.empty())
            {
                points.pop_back();
            }
        }



        Vector2 force{ 0.0f, 0.0f };
        if (input.GetKeyDown(SDL_SCANCODE_A)) force.x = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_D)) force.x = +speed;
        if (input.GetKeyDown(SDL_SCANCODE_W)) force.y = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_S)) force.y = +speed;

        player.SetVelocity(player.GetVelocity() + (force * time.GetDeltaTime()));
        player.Update(time.GetDeltaTime());

        //velocity += (force * time.GetDeltaTime());
        //position += (force * time.GetDeltaTime());

        //position.x = Wrap(0.0f, 1280.0f, position.x);
        //position.y = Wrap(0.0f, 1024.0f, position.y);

        renderer.SetColor(0.0f, 0.0f, 0.0f);
        renderer.Clear();

        for (int i = 0; i < (int)points.size() - 1; i++) 
        {
            renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat());
            renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        //renderer.SetColor(1.0f, 1.0f, 1.0f);
        //renderer.DrawFillRect(position.x - 20, position.y - 20, 40, 40);

        //for (int i = 0; i < 1000; i++)
        //{
        //    //renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat());
        //    renderer.SetColor(0.1f,0.1f,0.1f);
        //    renderer.DrawRect(rand() % 1280, rand() % 1024, rand() % 256, rand() % 256);
        //}

        player.Draw(renderer);
        //renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat());
        //renderer.DrawFillRect(40, 40, 40 ,40);

        

        renderer.Present(); // Render the screen
    }

    renderer.Shutdown();
    
    return 0;
}

