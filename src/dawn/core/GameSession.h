/*
 * Dawn Engine
 * Written by David Avedissian (c) 2012-2018 (git@dga.me.uk)
 */
#pragma once

#include "GameMode.h"

#include "core/EventSystem.h"
#include "scene/SceneManager.h"
#include "net/NetInstance.h"
#include "ui/UserInterface.h"

namespace dw {
struct DW_API GameSessionInfo {
    struct CreateLocalGame {
        String scene_name = "unknown";
    };

    struct CreateNetGame {
        String host = "localhost";  // host to bind to. usually 127.0.0.1.
        u16 port = 10000;
        u16 max_clients = 16;
        String scene_name = "unknown";
        // TODO: Transport.
    };

    struct JoinNetGame {
        String host = "localhost";
        u16 port = 10000;
        // TODO: Transport.
    };

    Variant<CreateLocalGame, CreateNetGame, JoinNetGame> start_info = CreateLocalGame{};

    // Graphics settings.
    bool headless = false;

    // Other parameters.
    HashMap<String, String> params;
};

class DW_API GameSession : public Object {
public:
    DW_OBJECT(GameSession);

    GameSession(Context* ctx, const GameSessionInfo& gsi);
    virtual ~GameSession();

    virtual void preUpdate();
    virtual void update(float dt);
    virtual void postUpdate();
    virtual void preRender();
    virtual void render(float interpolation);
    virtual void postRender();

    /// Access the current game mode.
    GameMode* gameMode() const;

    /// Access the user interface.
    UserInterface* ui() const;

    /// Access the scene graph.
    SceneGraph* sceneGraph() const;

    /// Access the scene manager.
    SceneManager* sceneManager() const;

    /// Access the event system for this game instance.
    EventSystem* eventSystem() const;

    /// Access the network instance. nullptr if networking is disabled.
    NetInstance* net() const;

protected:
    GameSessionInfo gsi_;

    UniquePtr<EventSystem> event_system_;
    UniquePtr<UserInterface> ui_;
    UniquePtr<SceneGraph> scene_graph_;
    UniquePtr<SceneManager> scene_manager_;
    UniquePtr<NetInstance> net_instance_;

    /// Sets a new game mode.
    void setGameMode(SharedPtr<GameMode> game_mode);

private:
    SharedPtr<GameMode> new_game_mode_;
    SharedPtr<GameMode> game_mode_;
};
}  // namespace dw
