# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.24)



project(Project)

# Optionel: Changer le dossier de sortie des exécutables (par défaut les exécutables sont mis dans le dossier build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# Trouve tous les fichiers .cpp dans mon répertoire src
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")

# Trouve tous les fichiers .cpp dans mon répertoire src préfixés par "main_"
file(GLOB_RECURSE SRC_MAIN_FILES CONFIGURE_DEPENDS "src/main*.cpp")

# On enlève les fichiers main_ des fichiers sources
list(REMOVE_ITEM SRC_FILES ${SRC_MAIN_FILES})

# Optionel: Affiche les fichiers trouvés
message(STATUS "SRC_FILES: ")
foreach(SRC_FILE ${SRC_FILES})
    message(STATUS "    ${SRC_FILE}")
endforeach()

message(STATUS "SRC_MAIN_FILES: ")
foreach(SRC_MAIN_FILE ${SRC_MAIN_FILES})
    message(STATUS "    ${SRC_MAIN_FILE}")
endforeach()

# Boucle sur chaque fichier cpp préfixé par "main_" pour créer autant d'exe
foreach(SRC_MAIN_FILE ${SRC_MAIN_FILES})
    # Nom du fichier sans le chemin ni l'extension
    # NAME_WE (Name Without Extension) précise que je veux uniquement le nom, sans l'extension
    get_filename_component(EXECUTABLE_NAME ${SRC_MAIN_FILE} NAME_WE)
    # On enlève le préfixe "main_" pour avoir un nom d'exécutable plus propre
    string(REPLACE "td" "" EXECUTABLE_NAME ${EXECUTABLE_NAME})

    # Ajoute un exécutable avec le nom du fichier et les autres fichiers sources
    add_executable(${EXECUTABLE_NAME} ${SRC_MAIN_FILE} ${SRC_FILES})
    # EXECUTABLE_NAME contient le nom du fichier exécutable
    # SRC_MAIN_FILE contient le chemin du fichier cpp (avec le préfixe "main_" et qui contient le point d'entrée main)
    # SRC_FILES contient tous les autres fichiers sources (Dans le cas où vous avez des fichiers sources partagés entre plusieurs exécutables)

    # On ajoute le dossier src pour que le compilateur trouve les headers
    target_include_directories(${EXECUTABLE_NAME} PRIVATE "src")

    # On indique que l'on veut utiliser le C++17
    target_compile_features(${EXECUTABLE_NAME} PUBLIC cxx_std_20)
    # set(CMAKE_CXX_STANDARD 20)


    # Quelques options de compilation pour ajouter des warnings
    if (MSVC)
        target_compile_options(${EXECUTABLE_NAME} PRIVATE /W3)
    else()
        target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors)
    endif()

endforeach()
