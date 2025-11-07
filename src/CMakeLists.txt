add_executable(Game)

target_sources(Game PRIVATE
    main.cpp
    Game.cpp
    Player.cpp
    Deck.cpp
)

target_link_libraries(Game
    PRIVATE
        fmt::fmt
        Utility
)

target_include_directories(Game 
    PRIVATE 
        ../include)

