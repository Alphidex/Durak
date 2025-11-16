add_executable(Game)

target_sources(Game PRIVATE
    main.cpp
    Game.cpp
    Player.cpp
    Deck.cpp
    Card.cpp
)

target_link_libraries(Game
    PRIVATE
        Utility
)

target_include_directories(Game 
    PRIVATE 
        ../include)

