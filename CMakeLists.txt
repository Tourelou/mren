cmake_minimum_required(VERSION 3.20)

project(mren LANGUAGES CXX)
# Appeler le projet du même nom que le répertoire
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

# Pour intégrer des modules maison
file(GLOB_RECURSE lib_source my_lib/*.cpp)
add_library(_modules_maison STATIC ${lib_source})

add_executable(${PROJECT_NAME} main.cpp)

# Vérifiez le système d'exploitation
if(APPLE)
    message(STATUS "Compilation sur macOS - Inclusion de librairie iconv")
    # Si nous sommes sur macOS, recherchez la bibliothèque iconv
    find_library(ICONV_LIBRARIES NAMES iconv)

    if(ICONV_LIBRARIES)
        message(STATUS "Librairie iconv trouvée: ${ICONV_LIBRARIES}")
        # Ajoutez ici votre logique pour inclure la bibliothèque iconv
        target_link_libraries(${PROJECT_NAME} _modules_maison ${ICONV_LIBRARIES})
    else()
        message(WARNING "Librairie iconv introuvable sur macOS")
    endif()
elseif(UNIX)
    # Si nous sommes sur Linux, ne faites rien ou ajoutez d'autres options si nécessaires
    message(STATUS "Compilation sur Linux - Pas de librairie iconv")
    target_link_libraries(${PROJECT_NAME} _modules_maison)
    else()
    # Pour d'autres systèmes d'exploitation, vous pouvez ajouter d'autres logiques si nécessaire
    message(STATUS "Compiling sur un système inconnu - Pas de librairie iconv")
    target_link_libraries(${PROJECT_NAME} _modules_maison)
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION "~/bin/")
